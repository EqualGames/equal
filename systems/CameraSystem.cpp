#include "CameraSystem.h"

namespace Tiled::Camera {

void system(Scene *scene) {
  const auto &player_transform =
      scene->registry->get<TransformComponent>(scene->player);

  scene->registry->patch<CameraComponent>(
      scene->camera, [player_transform](CameraComponent &camera) {
        camera.position = Position{
            (player_transform.position.x + player_transform.size.w / 2) -
                camera.size.w / 2,
            (player_transform.position.y + player_transform.size.h / 2) -
                camera.size.h / 2};
      });
}

} // namespace Tiled::Camera
