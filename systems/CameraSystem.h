#ifndef EQUAL_CAMERASYSTEM_H
#define EQUAL_CAMERASYSTEM_H

#include <entt/entt.hpp>
#include "../components/Transform.h"
#include "../components/Camera.h"

void camera_system(entt::registry &registry, entt::entity &camera_entity, entt::entity &player_entity);

#endif //EQUAL_CAMERASYSTEM_H
