#ifndef EQUAL_MAP_H
#define EQUAL_MAP_H

#include "../core/Types.h"
#include <vector>
#include <map>
#include <cstdint>

struct Tile {
    enum Flags : uint8_t {
        None = 1 << 0,
        Collision = 1 << 1,
    };

    uint32_t texture_id{0};
    Position position{0, 0};
    uint8_t flags{Flags::None};
};

struct Layer {
    std::vector<Tile *> tiles{};
};

struct Floor {
    int number{0};
    std::vector<Layer *> layers{};
};


struct Map {
    Size tile_size{32, 32};
    std::map<uint32_t, SDL_Texture *> textures{};
    std::vector<Floor *> floors{};
};

#endif //EQUAL_MAP_H
