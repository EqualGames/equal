#ifndef EQUAL_MAP_H
#define EQUAL_MAP_H

#include "../components/RigidBody.h"
#include "../components/Sprite.h"
#include "../components/Transform.h"
#include "../core/Helpers.h"
#include "../core/Types.h"
#include <SDL2/SDL.h>
#include <array>
#include <cstdint>
#include <entt/entt.hpp>
#include <map>
#include <pugixml.hpp>
#include <utility>
#include <vector>

struct Tile;
struct Tileset;

enum ThingOrder : uint32_t {
  GROUND = 0,
  GROUND_BORDER = 1,
  /* Walls */
  ON_BOTTOM = 2,
  /* Doors */
  ON_TOP = 3,
  CREATURE = 4,
  OTHER = 5,
};

struct Map {
  static const uint32_t MAX_TILE_VISIBLE_ENTITIES = 6;
  static const uint32_t MAX_TILE_ENTITIES = 32;
  static const uint32_t MAX_FLOOR_LAYERS = 32;

  Size tile_size{32, 32};
  std::vector<Tileset> tilesets{};
  std::vector<Tile *> tiles{};

  Map(entt::registry &registry, const char *source, const char *types_source,
      SDL_Renderer *renderer);

  Tileset &get_tileset(uint32_t gid);

  bool has_tile(const Position &position);
  bool has_tile(const Position &position) const;
  Tile *get_tile(const Position &position);
  Tile *get_tile(const Position &position) const;

  void attach(entt::registry &registry, entt::entity entity);
  int get_depth(int sprite_depth, const Position &position) const;
  static int make_depth(Tile *tile, ThingOrder order);

  bool has_collision(const Position &position);
  Position get_next_tile(entt::entity entity, const Position &position,
                         const DirectionalStatus &direction);
};

struct Tile {
  int index{0};
  bool collision{false};
  Position position{0, 0};
  std::vector<entt::entity> entities{};

  bool operator==(const Tile &right) const {
    return this->position.x == right.position.x &&
           this->position.y == right.position.y &&
           this->position.z == right.position.z;
  }

  bool operator!=(const Tile &right) const {
    return this->position.x != right.position.x ||
           this->position.y != right.position.y ||
           this->position.z != right.position.z;
  }
};

inline ThingOrder get_order_from_type(const std::string &name) {
  if (name == "Ground") {
    return ThingOrder::GROUND;
  }

  if (name == "Wall" || name == "Tree") {
    return ThingOrder::ON_BOTTOM;
  }

  if (name == "Creature") {
    return ThingOrder::CREATURE;
  }

  return ThingOrder::OTHER;
}

struct Tileset {
  uint32_t first_gid{0};
  Size tile_size{32, 32};
  Size texture_size{0, 0};
  SDL_Texture *texture{nullptr};

  SDL_Rect get_texture_position(uint32_t gid);
};

#endif // EQUAL_MAP_H
