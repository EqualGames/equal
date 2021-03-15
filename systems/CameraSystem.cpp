#include "CameraSystem.h"

void camera_system(entt::registry &registry, const entt::entity &camera_entity,
                   const entt::entity &player_entity) {
  auto &cam = registry.get<Camera>(camera_entity);
  auto &player = registry.get<Transform>(player_entity);

  cam.position.x =
      ((player.position.x * 32) + (player.size.w / 2)) - (cam.size.w / 2);
  cam.position.y =
      ((player.position.y * 32) + (player.size.h / 2)) - (cam.size.h / 2);
}
