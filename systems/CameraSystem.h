#ifndef EQUAL_CAMERA_SYSTEM_H
#define EQUAL_CAMERA_SYSTEM_H

#include "../components/CameraComponent.h"
#include "../components/TransformComponent.h"
#include "../core/Map.h"
#include "../core/Scene.h"
#include "../core/Types.h"

namespace CameraSystem {

void run(const Ref<Map> &map, entt::registry &registry, entt::entity camera_entity, entt::entity target_entity);

} // namespace CameraSystem

#endif // EQUAL_CAMERA_SYSTEM_H
