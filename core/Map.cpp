#include "Map.h"
#include "../components/PlayerComponent.h"

Map::Map(Scene *scene, const char *source, const char *types_source) {
  state.store(LoadingState::IDLE);
  thread = make_scope<std::thread>([this, scene, source, types_source]() {
    state.store(LoadingState::STARTED);

    std::map<std::string, bool> collisions{};

    EQ_LOG("\tReading the object types\n");
    {
      pugi::xml_document types_doc;
      auto types_result = types_doc.load_file(types_source);

      if (!types_result) {
        EQ_LOG("XML [%s] parsed with errors, offset %ti (error "
               "at[...%s])\n%s\n\n",
               types_source, types_result.offset,
               (types_source + types_result.offset),
               types_result.description());

        EQ_THROW("Error on read the map file");
      }

      auto $types = types_doc.child("objecttypes");

      for (auto $type = $types.child("objecttype"); $type;
           $type = $type.next_sibling("objecttype")) {

        std::string type_name = $type.attribute("name").as_string();

        for (auto $property = $type.child("property"); $property;
             $property = $property.next_sibling("property")) {

          std::string prop_name = $property.attribute("name").as_string();
          std::string prop_value = $property.attribute("default").as_string();

          if (prop_name == "collision" && prop_value == "true") {
            collisions.emplace(type_name, true);
          }
        }
      }
    }

    EQ_LOG("\tReading the map file\n");
    pugi::xml_document map_doc;
    auto result = map_doc.load_file(source);

    if (!result) {
      EQ_LOG("XML [%s] parsed with errors, offset %ti (error at "
             "[...%s])\n%s\n\n",
             source, result.offset, (source + result.offset),
             result.description());

      EQ_THROW("Error on read the map file");
    }

    auto $map = map_doc.child("map");

    size = Size{$map.attribute("width").as_int(),
                $map.attribute("height").as_int()};
    tiles.resize(size.w * size.h);

    std::map<uint32_t, std::map<uint32_t, std::string>> texture_types{};

    EQ_LOG("\tReading the tilesets\n");
    {
      for (auto $tileset = $map.child("tileset"); $tileset;
           $tileset = $tileset.next_sibling("tileset")) {

        Tileset tileset{};
        tileset.first_gid = $tileset.attribute("firstgid").as_uint();
        tileset.tile_size = Size{$tileset.attribute("tilewidth").as_uint(),
                                 $tileset.attribute("tileheight").as_uint()};

        auto $tileset_image = $tileset.child("image");
        tileset.name =
            split_pair(std::filesystem::path(
                           $tileset_image.attribute("source").as_string())
                           .filename()
                           .string(),
                       '.')
                .first;
        tileset.texture_size =
            Size{$tileset_image.attribute("width").as_uint(),
                 $tileset_image.attribute("height").as_uint()};

        std::map<uint32_t, std::string> types;
        for (auto $tileset_tile = $tileset.child("tile"); $tileset_tile;
             $tileset_tile = $tileset_tile.next_sibling("tile")) {

          uint32_t id = $tileset_tile.attribute("id").as_uint();
          std::string tile_type = $tileset_tile.attribute("type").as_string();

          types.emplace(id, tile_type);
        }

        texture_types.emplace(tileset.first_gid, types);
        tilesets.emplace_back(tileset);
      }
    }

    EQ_LOG("\tReading the tiles\n");
    {
      for (auto $floor = $map.child("group"); $floor;
           $floor = $floor.next_sibling("group")) {
        if (!$floor.attribute("visible").empty()) {
          continue;
        }

        int floor_number =
            strtol(split_pair($floor.attribute("name").as_string(), ' ')
                       .second.c_str(),
                   nullptr, 10);

        int layer_number = 0;
        for (auto $layer = $floor.first_child(); $layer;
             $layer = $layer.next_sibling()) {

          if (!$layer.attribute("visible").empty()) {
            continue;
          }

          int cx = 0;
          int cy = 0;
          int cw = $layer.attribute("width").as_int();
          int ch = $layer.attribute("height").as_int();

          for (auto $layer_data = $layer.child("data"); $layer_data;
               $layer_data = $layer_data.next_sibling("data")) {

            //            int chunk_index = 0;
            //            for (auto $chunk = $layer_data.child("chunk"); $chunk;
            //                 $chunk = $chunk.next_sibling("chunk")) {
            //
            //              int cx = $chunk.attribute("x").as_int();
            //              int cy = $chunk.attribute("y").as_int();
            //              int cw = $chunk.attribute("width").as_int();
            //              int ch = $chunk.attribute("height").as_int();

            int tile_index = 0;
            for (auto $tile = $layer_data.child("tile"); $tile;
                 $tile = $tile.next_sibling("tile")) {

              if ($tile.attribute("gid").empty()) {
                tile_index += 1;
                continue;
              }

              uint32_t gid = $tile.attribute("gid").as_uint();
              Position tile_position{(tile_index % cw), (tile_index / ch),
                                     floor_number};

              auto tile = make_ref<Tile>();
              tile->position =
                  Position{(cx + tile_position.x), (cy + tile_position.y),
                           tile_position.z};

              tile->index = tile->position.y * (int)size.h + tile->position.x;

              bool is_new_tile = true;

              if (has_tile(tile->position)) {
                is_new_tile = false;
                tile = get_tile(tile->position);
              }

              entt::entity thing_entity = scene->registry.create();

              TransformComponent &transform =
                  scene->registry.emplace<TransformComponent>(thing_entity);
              transform.position = tile->position;
              transform.size = tile_size;

              SpriteComponent &sprite =
                  scene->registry.emplace<SpriteComponent>(thing_entity);
              auto tileset = get_tileset(gid);

              sprite.texture_id = tileset.name;
              sprite.transform = tileset.get_texture_position(gid);

              auto tileset_types = texture_types.find(tileset.first_gid);

              if (tileset_types == texture_types.end()) {
                EQ_THROW("Map::make_map = invalid tileset types");
              }

              auto type_name =
                  tileset_types->second.find(gid - tileset.first_gid);

              if (type_name == tileset_types->second.end()) {
                EQ_THROW("Map::make_map = invalid tileset type name");
              }

              scene->registry.emplace<TagComponent>(thing_entity,
                                                    type_name->second);

              sprite.depth = tile->make_depth();

              if (type_name->second == "Tree" || type_name->second == "Wall") {
                sprite.depth += 1;
                if (!tile->collision) {
                  tile->collision = true;
                }

                RigidBodyComponent &rb =
                    scene->registry.emplace<RigidBodyComponent>(thing_entity);

                if (type_name->second == "Tree") {
                  transform.size = transform.size * 2;

                  rb.position = transform.position;
                  rb.size = transform.size / 2;
                }

                if (type_name->second == "Wall") {
                  transform.size = Size{transform.size.w, transform.size.h * 2};

                  rb.position = transform.position;
                  rb.size = Size{transform.size.w, transform.size.h / 2};
                }
              }

              tile->entities.emplace_back(thing_entity);

              if (is_new_tile) {
                tiles.insert(tiles.begin() + tile->index, tile);
              }

              tile_index += 1;
            }
            //
            //              chunk_index += 1;
            //            }
          }

          layer_number += 1;
        }
      }
    }

    state.store(LoadingState::FINISHED);
  });
}

Tileset &Map::get_tileset(uint32_t gid) {
  if (this->tilesets.empty()) {
    EQ_THROW("Map::get_tileset() = no tileset available");
  }

  auto it = std::find_if(
      this->tilesets.rbegin(), this->tilesets.rend(),
      [&gid](const Tileset &tileset) { return gid >= tileset.first_gid; });

  if (it == this->tilesets.rend()) {
    EQ_THROW("Map::get_tileset() = invalid tileset");
  }

  return *it;
}

bool Map::has_tile(const Position &position) {
  if (tiles.empty()) {
    return false;
  }

  auto index = position.y * size.h + position.x;

  if (index >= tiles.size()) {
    return false;
  }

  auto tile = tiles.at(index);

  return !!tile;
}

const Ref<Tile> &Map::get_tile(const Position &position) {
  if (!this->has_tile(position)) {
    EQ_THROW("Map::get_tile() = invalid tile");
  }

  return tiles.at(position.y * size.h + position.x);
}

void Map::attach(entt::registry &registry, entt::entity entity) {
  const auto &transform = registry.get<TransformComponent>(entity);

  auto tile = this->get_tile(transform.position);

  registry.patch<TransformComponent>(entity,
                                     [tile](TransformComponent &transform) {
                                       transform.position.z = tile->position.z;
                                     });

  registry.patch<SpriteComponent>(entity, [tile](SpriteComponent &sprite) {
    sprite.depth = tile->make_depth() + 2;
  });

  tile->entities.emplace_back(entity);
}

bool Map::has_collision(const Position &position) {
  if (!this->has_tile(position)) {
    return true;
  }

  auto tile = this->get_tile(position);

  return tile->collision;
}

const Ref<Tile> &Map::get_next_tile(entt::entity entity,
                                    const Position &position,
                                    const ControllerState &controller) {
  Position next_position{position};

  if (controller.Up) {
    next_position.y -= 1;

    if (has_collision(next_position)) {
      next_position.y += 1;
    }
  }

  if (controller.Down) {
    next_position.y += 1;

    if (has_collision(next_position)) {
      next_position.y -= 1;
    }
  }

  if (controller.Left) {
    next_position.x -= 1;

    if (has_collision(next_position)) {
      next_position.x += 1;
    }
  }

  if (controller.Right) {
    next_position.x += 1;

    if (has_collision(next_position)) {
      next_position.x -= 1;
    }
  }

  auto &tile = get_tile(position);
  auto &next_tile = get_tile(next_position);

  auto it = std::find(tile->entities.begin(), tile->entities.end(), entity);

  if (it != tile->entities.end()) {
    tile->entities.erase(it);
    next_tile->entities.emplace_back(entity);
  } else {
    EQ_LOG("Are you trying to remove from the same tile again?\n")
  }

  return next_tile;
}
