#include "Map.h"

Tile *Floor::get_tile(const Position &position) {
  if (this->tiles.empty()) {
    return nullptr;
  }

  auto it = std::find_if(
      this->tiles.begin(), this->tiles.end(),
      [&position](const Tile *tile) { return tile->position == position; });

  if (it != this->tiles.end()) {
    return *it;
  }

  return nullptr;
}

std::string Tileset::get_tile_type(uint32_t &gid) {
  if (gid == 0) {
    return "";
  }

  auto it = this->tile_type.find(gid - this->first_gid);

  if (it != this->tile_type.end()) {
    return it->second;
  }

  return "";
}

SDL_Rect Tileset::get_texture_position(uint32_t &gid) {
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

uint32_t Map::get_type_flags(const std::string &type_name) {
  if (this->types.empty() || type_name.empty()) {
    return TileFlag::NO_FLAG;
  }

  auto it = std::find_if(
      this->types.begin(), this->types.end(),
      [&type_name](const TileType *type) { return type->name == type_name; });

  if (it != this->types.end()) {
    return (*it)->flags;
  }

  return TileFlag::NO_FLAG;
}

Position Map::get_next_tile(const entt::entity &entity,
                            const Position &position, int direction,
                            int floor_number) {
  auto floor = this->floors.at(floor_number);
  if (!floor) {
    throw std::exception("get_next_tile: invalid floor");
  }

  auto tile = floor->get_tile(position);
  if (!tile) {
    return position;
  }

  Position next_position{position};

  if (direction & Direction::Up) {
    next_position.y -= 1;

    if (this->has_collision(next_position, floor_number)) {
      next_position.y += 1;
    }
  }

  if (direction & Direction::Down) {
    next_position.y += 1;

    if (this->has_collision(next_position, floor_number)) {
      next_position.y -= 1;
    }
  }

  if (direction & Direction::Left) {
    next_position.x -= 1;

    if (this->has_collision(next_position, floor_number)) {
      next_position.x += 1;
    }
  }

  if ((direction & Direction::Right) == Direction::Right) {
    next_position.x += 1;

    if (this->has_collision(next_position, floor_number)) {
      next_position.x -= 1;
    }
  }

  Tile *next_tile = floor->get_tile(next_position);

  if (tile != next_tile) {
    auto it = std::find_if(
        tile->things.rbegin(), tile->things.rend(),
        [&entity](const Thing *thing) { return thing->id == entity; });

    Thing *thing = *it;

    next_tile->things.emplace_back(thing);

    tile->things.erase(std::next(it).base());
    return next_tile->position;
  }

  return position;
}

bool Map::has_collision(const Position &position, int floor_number) {
  auto floor = this->floors.at(floor_number);

  if (!floor) {
    throw std::exception("has_collision: invalid floor");
  }

  auto tile = floor->get_tile(position);

  if (!tile) {
    return true;
  }

  bool collision = false;

  for (auto thing : tile->things) {
    if (thing->flags & TileFlag::COLLISION) {
      collision = true;
      break;
    }
  }

  return collision;
}

void Map::add_thing(const Position &position, int floor_number,
                    int layer_number, Thing *thing) {
  auto floor = this->floors.at(floor_number);

  if (!floor) {
    throw std::exception("add_thing: invalid floor");
  }

  auto tile = floor->get_tile(position);

  if (!tile) {
    throw std::exception("add_thing: invalid tile");
  }

  tile->things.emplace(tile->things.begin() + layer_number, thing);
}

Tileset *Map::get_tileset(const uint32_t &gid) {
  if (this->tilesets.empty()) {
    return nullptr;
  }

  auto it = std::find_if(
      this->tilesets.rbegin(), this->tilesets.rend(),
      [&gid](const Tileset *tileset) { return tileset->first_gid <= gid; });

  if (it != this->tilesets.rend()) {
    return *it;
  }

  return nullptr;
}

Map make_map(const char *source, const char *types_source,
             SDL_Renderer *renderer) {
  Map map{};

  pugi::xml_document types_doc;
  auto types_result = types_doc.load_file(types_source);

  if (!types_result) {
    printf("XML [%s] parsed with errors, offset %i (error at [...%s])\n%s\n\n",
           types_source, types_result.offset,
           (types_source + types_result.offset), types_result.description());

    throw std::exception("Error on read the map file");
  }

  auto $types = types_doc.child("objecttypes");

  for (auto $type = $types.child("objecttype"); $type;
       $type = $type.next_sibling("objecttype")) {

    TileType *type = new TileType{};
    type->name = $type.attribute("name").as_string();

    for (auto $property = $type.child("property"); $property;
         $property = $property.next_sibling("property")) {

      std::string prop_name = $property.attribute("name").as_string();
      std::string prop_value = $property.attribute("default").as_string();

      if (prop_name == "collision" && prop_value == "true") {
        type->flags |= TileFlag::COLLISION;
      }
    }

    map.types.emplace_back(type);
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

  for (auto $tileset = $map.child("tileset"); $tileset;
       $tileset = $tileset.next_sibling("tileset")) {

    Tileset *tileset = new Tileset{};
    tileset->first_gid = $tileset.attribute("firstgid").as_uint();
    tileset->tile_size = Size{$tileset.attribute("tilewidth").as_int(),
                              $tileset.attribute("tileheight").as_int()};

    auto $tileset_image = $tileset.child("image");
    std::string texture_name =
        split_pair($tileset_image.attribute("source").as_string(), '.').first;

    tileset->texture_size = Size{$tileset_image.attribute("width").as_int(),
                                 $tileset_image.attribute("height").as_int()};
    tileset->texture =
        load_texture(renderer, "assets/map/" + texture_name + ".png");

    for (auto $tileset_tile = $tileset.child("tile"); $tileset_tile;
         $tileset_tile = $tileset_tile.next_sibling("tile")) {

      uint32_t id = $tileset_tile.attribute("id").as_uint();
      std::string tile_type = $tileset_tile.attribute("type").as_string();

      tileset->tile_type.emplace(id, tile_type);
    }

    map.tilesets.emplace_back(tileset);
  }

  for (auto $floor = $map.child("group"); $floor;
       $floor = $floor.next_sibling("group")) {
    if (!$floor.attribute("visible").empty()) {
      continue;
    }

    Floor *floor = new Floor{};

    floor->number = strtol(
        split_pair($floor.attribute("name").as_string(), ' ').second.c_str(),
        nullptr, 10);

    for (auto $layer = $floor.first_child(); $layer;
         $layer = $layer.next_sibling()) {
      if (!$layer.attribute("visible").empty()) {
        continue;
      }

      for (auto $layer_data = $layer.child("data"); $layer_data;
           $layer_data = $layer_data.next_sibling("data")) {

        for (auto $layer_chunk = $layer_data.child("chunk"); $layer_chunk;
             $layer_chunk = $layer_chunk.next_sibling("chunk")) {

          int cx = $layer_chunk.attribute("x").as_int();
          int cy = $layer_chunk.attribute("y").as_int();
          int cw = $layer_chunk.attribute("width").as_int();
          int ch = $layer_chunk.attribute("height").as_int();

          int tile_index = 0;
          for (auto $tile = $layer_chunk.child("tile"); $tile;
               $tile = $tile.next_sibling("tile")) {
            Position tile_position{cx + (tile_index % cw),
                                   cy + (tile_index / ch)};

            bool is_new_tile = false;
            Tile *tile = floor->get_tile(tile_position);

            if (!tile) {
              is_new_tile = true;
              tile = new Tile{};
              tile->position = tile_position;
            }

            if (!$tile.attribute("gid").empty()) {
              Thing *thing = new Thing{};

              thing->gid = $tile.attribute("gid").as_uint();

              auto tileset = map.get_tileset(thing->gid);
              thing->type_name = tileset->get_tile_type(thing->gid);
              thing->flags = map.get_type_flags(thing->type_name);

              tile->things.emplace_back(thing);

              if (thing->type_name == "Tree" || thing->type_name == "Wall") {
                Position sub_position{tile_position.x, tile_position.y};

                if (thing->type_name == "Tree") {
                  sub_position.x -= 1;
                }

                if (thing->type_name == "Wall") {
                  sub_position.y -= 1;
                }

                Tile *sub_tile = floor->get_tile(sub_position);

                bool is_new_sub_tile = false;

                if (!tile) {
                  is_new_sub_tile = true;
                  sub_tile = new Tile{};
                  sub_tile->position = sub_position;
                }

                Thing *sub_thing = new Thing{};
                sub_thing->gid = 0;
                sub_thing->flags = TileFlag::COLLISION;

                sub_tile->things.emplace_back(sub_thing);

                if (is_new_sub_tile) {
                  floor->tiles.emplace_back(sub_tile);
                }
              }
            }

            if (is_new_tile) {
              floor->tiles.emplace_back(tile);
            }

            tile_index = tile_index + 1;
          }
        }
      }
    }

    map.floors.emplace_back(floor);
  }

  return map;
}
