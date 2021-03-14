#include "CameraSystem.h"

void camera_system(entt::registry &registry, entt::entity &camera_entity, entt::entity &player_entity) {
    auto& cam = registry.get<Camera>(camera_entity);
    auto& player = registry.get<Transform>(player_entity);

    cam.position.x = (player.position.x + (player.size.w / 2)) - (cam.size.w / 2);
    cam.position.y = (player.position.y + (player.size.h / 2)) - (cam.size.h / 2);
}
