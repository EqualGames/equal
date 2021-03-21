#ifndef EQUAL_CAMERA_SYSTEM_H
#define EQUAL_CAMERA_SYSTEM_H

#include "../components/Camera.h"
#include "../components/Transform.h"
#include "../core/Application.h"
#include <entt/entt.hpp>

void camera_system(Application *app, entt::entity camera_entity, entt::entity player_entity);

#endif // EQUAL_CAMERA_SYSTEM_H
