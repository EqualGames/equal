#pragma once

#include "Types.h"
#include <vector>

namespace eq {

    struct Tile {
        bool collision{false};
        uint32_t index{0};
        Position position{0, 0};
        std::vector<entt::entity> entities{};

        inline int make_depth() const { return index + (int) entities.size(); }

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

}// namespace eq
