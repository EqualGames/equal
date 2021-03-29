#include "CameraSystem.h"

namespace CameraSystem {

void run(const Ref<Map> &map, entt::registry &registry,
         entt::entity camera_entity, entt::entity target_entity) {
  const auto &target = registry.get<TransformComponent>(target_entity);

  // ? Converts target position to world position
  const auto target_position = Position{target.position.x * map->tile_size.w,
                                        target.position.y * map->tile_size.h};

  auto &camera = registry.get<CameraComponent>(camera_entity);

  if (camera.position != target_position) {
    const auto camera_size = Position{camera.size.w / 2, camera.size.h / 2};
    const auto target_size = Position{target.size.w / 2, target.size.h / 2};

    camera.position = target_position + target_size - camera_size;
  }
}

} // namespace CameraSystem
