#pragma once

#include "Texture.h"
#include "Types.h"

namespace eq {

    struct Tileset {
        std::string name{};
        uint32_t first_gid{0};
        Size tile_size{32, 32};
        Size texture_size{0, 0};

        Transform get_texture_position(uint32_t gid) {
            int id = (int) (gid - this->first_gid);

            return Transform{
                    Position{
                            (int) tile_size.w * (id % ((int) texture_size.w / (int) tile_size.w)),
                            (int) tile_size.h * ((id / ((int) texture_size.w / (int) tile_size.w)) %
                                                 ((int) texture_size.h / (int) tile_size.h)),
                    },
                    tile_size};
        }
    };

}// namespace eq
