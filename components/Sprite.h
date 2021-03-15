#ifndef EQUAL_SPRITE_H
#define EQUAL_SPRITE_H

#include "../core/Types.h"
#include <tuple>
#include <vector>

enum SpriteRenderType {
  BORDER,
  FILL,
  FULL,
};

struct Sprite {
  Direction direction{Direction::Down};
  SpriteRenderType render_type{SpriteRenderType::FULL};
  Color color{};
  std::vector<std::tuple<SDL_Texture *, Position, Size>> textures{};
};

#endif // EQUAL_SPRITE_H
