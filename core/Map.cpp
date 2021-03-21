#include "Map.h"

Map::Map(entt::registry &registry, const char *source, const char *types_source,
         SDL_Renderer *renderer) {
  std::map<std::string, bool> collisions{};

  // Object types
  {
    pugi::xml_document types_doc;
    auto types_result = types_doc.load_file(types_source);

    if (!types_result) {
      printf(
          "XML [%s] parsed with errors, offset %i (error at [...%s])\n%s\n\n",
          types_source, types_result.offset,
          (types_source + types_result.offset), types_result.description());

      throw std::exception("Error on read the map file");
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

  pugi::xml_document map_doc;
  auto result = map_doc.load_file(source);

  if (!result) {
    printf("XML [%s] parsed with errors, offset %i (error at [...%s])\n%s\n\n",
           source, result.offset, (source + result.offset),
           result.description());

    throw std::exception("Error on read the map file");
  }

  auto $map = map_doc.child("map");

  std::map<uint32_t, std::map<uint32_t, std::string>> texture_types{};
  // Tilesets
  {
    for (auto $tileset = $map.child("tileset"); $tileset;
         $tileset = $tileset.next_sibling("tileset")) {

      Tileset tileset{};
      tileset.first_gid = $tileset.attribute("firstgid").as_uint();
      tileset.tile_size = Size{$tileset.attribute("tilewidth").as_int(),
                               $tileset.attribute("tileheight").as_int()};

      auto $tileset_image = $tileset.child("image");
      std::string texture_name =
          split_pair($tileset_image.attribute("source").as_string(), '.').first;

      tileset.texture_size = Size{$tileset_image.attribute("width").as_int(),
                                  $tileset_image.attribute("height").as_int()};
      tileset.texture =
          load_texture(renderer, "assets/map/" + texture_name + ".png");

      std::map<uint32_t, std::string> types;
      for (auto $tileset_tile = $tileset.child("tile"); $tileset_tile;
           $tileset_tile = $tileset_tile.next_sibling("tile")) {

        uint32_t id = $tileset_tile.attribute("id").as_uint();
        std::string tile_type = $tileset_tile.attribute("type").as_string();

        types.emplace(id, tile_type);
      }

      texture_types.emplace(tileset.first_gid, types);
      this->tilesets.emplace_back(tileset);
    }
  }

  // Tiles
  {
    for (auto $floor = $map.child("group"); $floor;
         $floor = $floor.next_sibling("group")) {
      if (!$floor.attribute("visible").empty()) {
        continue;
      }

      int floor_number = strtol(
          split_pair($floor.attribute("name").as_string(), ' ').second.c_str(),
          nullptr, 10);

      int layer_number = 0;
      for (auto $layer = $floor.first_child(); $layer;
           $layer = $layer.next_sibling()) {

        if (!$layer.attribute("visible").empty()) {
          continue;
        }
        layer_number += 1;

        if (layer_number >= Map::MAX_FLOOR_LAYERS) {
          continue;
        }

        for (auto $layer_data = $layer.child("data"); $layer_data;
             $layer_data = $layer_data.next_sibling("data")) {

          for (auto $chunk = $layer_data.child("chunk"); $chunk;
               $chunk = $chunk.next_sibling("chunk")) {

            int cx = $chunk.attribute("x").as_int();
            int cy = $chunk.attribute("y").as_int();
            int cw = $chunk.attribute("width").as_int();
            int ch = $chunk.attribute("height").as_int();

            int tile_index = 0;
            for (auto $tile = $chunk.child("tile"); $tile;
                 $tile = $tile.next_sibling("tile")) {

              if ($tile.attribute("gid").empty()) {
                tile_index = tile_index + 1;
                continue;
              }

              uint32_t gid = $tile.attribute("gid").as_uint();
              Position tile_position{(tile_index % cw), (tile_index / ch),
                                     floor_number};

              Tile *tile = new Tile{};
              tile->index =
                  (tile_position.x + cx) + (tile_position.y + cy) * cw +
                  (tile_position.z * (int)(Map::MAX_FLOOR_LAYERS + 1));

              tile->position = Position{
                  (cx + tile_position.x) * this->tile_size.w,
                  (cy + tile_position.y) * this->tile_size.h, tile_position.z};

              bool is_new_tile = true;

              if (this->has_tile(tile->position)) {
                is_new_tile = false;
                tile = this->get_tile(tile->position);

                if (tile->entities.size() >= Map::MAX_TILE_ENTITIES) {
                  continue;
                }
              }

              entt::entity thing_entity = registry.create();

              Transform &transform = registry.emplace<Transform>(thing_entity);
              transform.position = tile->position;
              transform.size = this->tile_size;

              Sprite &sprite = registry.emplace<Sprite>(thing_entity);
              auto tileset = this->get_tileset(gid);
              auto rect = tileset.get_texture_position(gid);
              sprite.textures.emplace_back(
                  std::make_tuple(tileset.texture, Position{rect.x, rect.y},
                                  Size{rect.w, rect.h}));

              auto tileset_types = texture_types.find(tileset.first_gid);
              if (tileset_types == texture_types.end()) {
                throw std::exception("Map::make_map = invalid tileset types");
              }

              auto type_name =
                  tileset_types->second.find(gid - tileset.first_gid);
              if (type_name == tileset_types->second.end()) {
                throw std::exception(
                    "Map::make_map = invalid tileset type name");
              }

              sprite.depth =
                  Map::make_depth(tile, get_order_from_type(type_name->second));

              if (type_name->second == "Tree" || type_name->second == "Wall") {
                if (!tile->collision) {
                  tile->collision = true;
                }

                RigidBody &rb = registry.emplace<RigidBody>(thing_entity);

                if (type_name->second == "Tree") {
                  transform.size = transform.size * 2;

                  rb.position = transform.position;
                  rb.size = transform.size / 2;
                }

                if (type_name->second == "Wall") {
                  transform.size = Size{transform.size.w, transform.size.h * 2};

                  rb.position =
                      Position{transform.position.x,
                               transform.position.y - transform.size.h / 2,
                               transform.position.z};
                  rb.size = transform.size;
                }
              }

              tile->entities.emplace_back(thing_entity);

              if (is_new_tile) {
                this->tiles.emplace_back(tile);
              }

              tile_index = tile_index + 1;
            }
          }
        }
      }
    }
  }
}

Tileset &Map::get_tileset(uint32_t gid) {
  if (this->tilesets.empty()) {
    throw std::exception("Map::get_tileset() = no tileset available");
  }

  auto it = std::find_if(
      this->tilesets.rbegin(), this->tilesets.rend(),
      [&gid](const Tileset &tileset) { return gid >= tileset.first_gid; });

  if (it == this->tilesets.rend()) {
    throw std::exception("Map::get_tileset() = invalid tileset");
  }

  return *it;
}

bool Map::has_tile(const Position &position) {
  if (this->tiles.empty()) {
    return false;
  }

  auto it = std::find_if(
      this->tiles.begin(), this->tiles.end(),
      [&position](const Tile *tile) { return tile->position == position; });

  return it != this->tiles.end();
}

bool Map::has_tile(const Position &position) const {
  if (this->tiles.empty()) {
    return false;
  }

  auto it = std::find_if(
      this->tiles.begin(), this->tiles.end(),
      [&position](const Tile *tile) { return tile->position == position; });

  return it != this->tiles.end();
}

Tile *Map::get_tile(const Position &position) {
  if (!this->has_tile(position)) {
    throw std::exception("Map::get_tile() = invalid tile");
  }

  auto it = std::find_if(
      this->tiles.begin(), this->tiles.end(),
      [&position](const Tile *tile) { return tile->position == position; });

  return *it;
}

Tile *Map::get_tile(const Position &position) const {
  if (!this->has_tile(position)) {
    throw std::exception("Map::get_tile() = invalid tile");
  }

  auto it = std::find_if(
      this->tiles.begin(), this->tiles.end(),
      [&position](const Tile *tile) { return tile->position == position; });

  return *it;
}

void Map::attach(entt::registry &registry, entt::entity entity) {
  auto [transform, sprite] = registry.get<Transform, Sprite>(entity);

  auto tile = this->get_tile(transform.position);
  tile->entities.emplace_back(entity);

  transform.position.z = tile->position.z;
  sprite.depth = Map::make_depth(tile, ThingOrder::CREATURE);
}

int Map::get_depth(int sprite_depth, const Position &position) const {
  const auto tile = this->get_tile(position);

  return sprite_depth - tile->index;
}

int Map::make_depth(Tile *tile, ThingOrder order) {
  return tile->index + (int)order;
}

bool Map::has_collision(const Position &position) {
  if (!this->has_tile(position)) {
    return true;
  }

  auto tile = this->get_tile(position);

  return tile->collision;
}

Position Map::get_next_tile(entt::entity entity, const Position &position,
                            const DirectionalStatus &direction) {
  Position next_position = position;

  if (!this->has_tile(position)) {
    return next_position;
  }

  auto tile = this->get_tile(position);

  if (direction.up) {
    next_position.y -= this->tile_size.h;

    if (this->has_collision(next_position)) {
      next_position.y += this->tile_size.h;
    }
  }

  if (direction.down) {
    next_position.y += this->tile_size.h;

    if (this->has_collision(next_position)) {
      next_position.y -= this->tile_size.h;
    }
  }

  if (direction.left) {
    next_position.x -= this->tile_size.w;

    if (this->has_collision(next_position)) {
      next_position.x += this->tile_size.w;
    }
  }

  if (direction.right) {
    next_position.x += this->tile_size.w;

    if (this->has_collision(next_position)) {
      next_position.x -= this->tile_size.w;
    }
  }

  auto next_tile = this->get_tile(next_position);

  if (next_tile && tile != next_tile) {
    std::erase(tile->entities, entity);

    next_position = next_tile->position;

    next_tile->entities.emplace_back(entity);
  }

  return next_position;
}

SDL_Rect Tileset::get_texture_position(uint32_t gid) {
  int id = (int)(gid - this->first_gid);

  SDL_Rect rect{
      this->tile_size.w * (id % (this->texture_size.w / this->tile_size.w)),
      this->tile_size.h * ((id / (this->texture_size.w / this->tile_size.w)) %
                           (this->texture_size.h / this->tile_size.h)),
      this->tile_size.w,
      this->tile_size.h,
  };

  return rect;
}
