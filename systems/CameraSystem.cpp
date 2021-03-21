#include "CameraSystem.h"

void camera_system(Application *app, entt::entity camera_entity,
                   entt::entity player_entity) {
  auto &cam = app->registry.get<Camera>(camera_entity);
  const auto &player_transform = app->registry.get<Transform>(player_entity);

  cam.position.x = (player_transform.position.x + player_transform.size.w / 2) -
                   cam.size.w / 2;
  cam.position.y = (player_transform.position.y + player_transform.size.h / 2) -
                   cam.size.h / 2;


#ifdef DEBUG_CAMERA_SYSTEM
  printf("CameraSystem <- (%i %i) (%i %i)\n", cam.position.x, cam.position.y,
         cam.size.w, cam.size.h);
#endif
}
