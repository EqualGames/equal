#ifndef EQUAL_CAMERASYSTEM_H
#define EQUAL_CAMERASYSTEM_H

#include "../components/Camera.h"
#include "../components/Transform.h"
#include <entt/entt.hpp>

void camera_system(entt::registry &registry, const entt::entity &camera_entity,
                   const entt::entity &player_entity);

#endif // EQUAL_CAMERASYSTEM_H
