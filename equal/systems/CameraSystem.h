#pragma once

#include "../core/Entity.h"
#include "../core/Map.h"
#include "../core/Types.h"
#include "../export.h"

namespace eq::CameraSystem {

    EQ_EXPORT void run(const Ref<Map> &map, Registry &registry,
                       Entity &camera_entity, Entity &target_entity);

}// namespace eq::CameraSystem
