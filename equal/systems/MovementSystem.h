#pragma once

#include "../core/Entity.h"
#include "../core/Map.h"
#include "../core/Types.h"
#include "../export.h"

namespace eq::MovementSystem {

    const float KEY_PRESSED_DELAY = 0.032f;

    EQ_EXPORT void run(const Ref<Map> &map, Registry &registry, Entity &entity,
                       float delta_time);

};// namespace eq::MovementSystem
