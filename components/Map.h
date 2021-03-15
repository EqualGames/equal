#ifndef EQUAL_MAP_H
#define EQUAL_MAP_H

#include "../core/Helpers.h"
#include "../core/Types.h"
#include <SDL2/SDL.h>
#include <cstdint>
#include <entt/entt.hpp>
#include <map>
#include <pugixml.hpp>
#include <vector>

enum TileFlag {
  NO_FLAG = 1 << 0,
  ENTITY = 1 << 1,
  COLLISION = 1 << 2,
};

struct Thing {
  entt::entity id{};
  std::string type_name{};
  uint32_t flags{TileFlag::NO_FLAG};
  uint32_t gid{0};
};

struct Tile {
  Position position{0, 0};
  std::vector<Thing *> things{};

  bool operator==(const Tile &right) const {
    return this->position.x == right.position.x &&
           this->position.y == right.position.y;
  }

  bool operator!=(const Tile &right) const {
    return this->position.x != right.position.x ||
           this->position.y != right.position.y;
  }
};

struct Floor {
  int number{0};
  std::vector<Tile *> tiles{};

  Tile *get_tile(const Position &position);
};

struct Tileset {
  uint32_t first_gid{0};
  Size tile_size{32, 32};
  Size texture_size{0, 0};
  std::map<std::uint32_t, std::string> tile_type{};
  SDL_Texture *texture{nullptr};

  std::string get_tile_type(uint32_t &gid);

  SDL_Rect get_texture_position(uint32_t &gid);
};

struct TileType {
  std::string name{};
  uint32_t flags{TileFlag::NO_FLAG};
};

struct Map {
  Size tile_size{32, 32};
  std::vector<Tileset *> tilesets{};
  std::vector<Floor *> floors{};
  std::vector<TileType *> types{};

  uint32_t get_type_flags(const std::string &type_name);

  Position get_next_tile(const entt::entity &entity, const Position &position,
                         int direction, int floor_number = 0);

  bool has_collision(const Position &position, int floor_number = 0);

  void add_thing(const Position &position, int floor_number, int layer_number,
                 Thing *thing);

  Tileset *get_tileset(const uint32_t &gid);
};

Map make_map(const char *source, const char *types_source,
             SDL_Renderer *renderer);

#endif // EQUAL_MAP_H
