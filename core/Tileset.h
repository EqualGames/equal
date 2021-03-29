#ifndef EQUAL_TILESET_H
#define EQUAL_TILESET_H

#include "Texture.h"
#include "Types.h"

struct Tileset {
  std::string name{};
  uint32_t first_gid{0};
  Size tile_size{32, 32};
  Size texture_size{0, 0};

  Transform get_texture_position(uint32_t gid);
};

#endif // EQUAL_TILESET_H
