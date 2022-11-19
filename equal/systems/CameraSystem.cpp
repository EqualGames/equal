#include "CameraSystem.h"
#include "../components/CameraComponent.h"
#include "../components/TransformComponent.h"

namespace eq::CameraSystem {

    void run(const Ref<Map> &map, Registry &registry, Entity &camera_entity,
             Entity &target_entity) {
        const auto &target = target_entity.get_component<TransformComponent>();
        auto &tile_size = map->tile_size;

        // ? Converts target position to world position
        const auto target_position = Position{target.position.x * (int) tile_size.w,
                                              target.position.y * (int) tile_size.h};

        auto &camera = camera_entity.get_component<CameraComponent>();

        if (camera.position != target_position) {
            const auto camera_size = Position{(int) camera.size.w / 2, (int) camera.size.h / 2};
            const auto target_size = Position{(int) target.size.w / 2, (int) target.size.h / 2};

            camera.position = target_position + target_size - camera_size;
        }
    }

}// namespace eq::CameraSystem
