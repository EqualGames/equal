#pragma once

#include "../components/PlayerComponent.h"
#include "../export.h"
#include "Entity.h"
#include "Tile.h"
#include "Tileset.h"
#include "Types.h"
#include <atomic>
#include <filesystem>
#include <pugixml.hpp>
#include <thread>
#include <vector>

namespace eq {

    class EQ_EXPORT Map {
    public:
        enum LoadingState { IDLE = 0,
                            STARTED = 1,
                            FINISHED = 2,
                            LOADED = 3 };
        Scope<std::thread> thread{nullptr};
        std::atomic_int state;

        Size size{0, 0};
        Size tile_size{32, 32};
        std::vector<Tileset> tilesets{};
        std::vector<Ref<Tile>> tiles{};

        Map() = default;

        void load_from(Scene *scene, const std::string &source, const std::string &types_source);

        Tileset &get_tileset(uint32_t gid);

        bool has_tile(const Position &position);
        Ref<Tile> &get_tile(const Position &position);
        bool has_collision(const Position &position);

        void attach(Entity &entity);
        const Ref<Tile> &get_next_tile(Entity &entity, const Position &position,
                                       const ControllerState &controller);
    };

}// namespace eq
