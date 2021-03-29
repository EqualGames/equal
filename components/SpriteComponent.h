#ifndef EQUAL_SPRITE_COMPONENT_H
#define EQUAL_SPRITE_COMPONENT_H

#include "../core/Texture.h"
#include "../core/Types.h"
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
  std::string texture_id{};
  Transform transform{};
};

#endif // EQUAL_SPRITE_COMPONENT_H
