#ifndef EQUAL_TILE_H
#define EQUAL_TILE_H

#include "Types.h"
#include <entt/entt.hpp>
#include <vector>

struct Tile {
  bool collision{false};
  uint32_t index{0};
  Position position{0, 0};
  std::vector<entt::entity> entities{};

  inline int make_depth() const { return index + (int)entities.size(); }

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

#endif // EQUAL_TILE_H
