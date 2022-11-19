#include "MovementSystem.h"
#include "../components/SpriteComponent.h"
#include "../components/TransformComponent.h"

namespace eq::MovementSystem {

    float keypress_time = 0.0f;

    void run(const Ref<Map> &map, Registry &registry, Entity &entity,
             float delta_time) {
        if (keypress_time < KEY_PRESSED_DELAY) {
            keypress_time += delta_time;
            return;
        }

        keypress_time = 0.0f;

        auto &player = entity.get_component<PlayerComponent>();
        auto &transform = entity.get_component<TransformComponent>();

        auto &tile =
                map->get_next_tile(entity, transform.position, player.controller);

        if (tile->position == transform.position) {
            return;
        }

        transform.position = tile->position;

        if (entity.has_component<SpriteComponent>()) {
//            Direction sprite_direction{Direction::None};
//
//            if (player.controller.Up) {
//                sprite_direction = Direction::Up;
//            } else if (player.controller.Down) {
//                sprite_direction = Direction::Down;
//            } else if (player.controller.Left) {
//                sprite_direction = Direction::Left;
//            } else if (player.controller.Right) {
//                sprite_direction = Direction::Right;
//            }

            auto depth = (tile->make_depth() - 1) + 2;

            auto sprite = entity.get_component<SpriteComponent>();
            sprite.depth = depth;
//            sprite.direction = sprite_direction;

            entity.replace_component<SpriteComponent>(sprite);
        }
    }

}// namespace eq::MovementSystem
