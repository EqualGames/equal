#include "Tileset.h"

Transform Tileset::get_texture_position(uint32_t gid) {
  int id = (int)(gid - this->first_gid);

  return Transform{
      Position{
          (int)tile_size.w * (id % ((int)texture_size.w / (int)tile_size.w)),
          (int)tile_size.h * ((id / ((int)texture_size.w / (int)tile_size.w)) %
                              ((int)texture_size.h / (int)tile_size.h)),
      },
      tile_size};
}
