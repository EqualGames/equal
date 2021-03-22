#ifndef EQUAL_SPRITE_COMPONENT_H
#define EQUAL_SPRITE_COMPONENT_H

#include "../core/Types.h"
#include <entt/core/hashed_string.hpp>
#include <tuple>
#include <vector>

enum SpriteRenderType {
  BORDER,
  FILL,
  FULL,
};

struct SpriteComponent {
  int depth{0};
  Direction direction{Direction::Down};
  SpriteRenderType render_type{SpriteRenderType::FULL};
  Color color{};
  std::vector<std::tuple<entt::hashed_string, Position, Size>> textures{};
};

#endif // EQUAL_SPRITE_COMPONENT_H
