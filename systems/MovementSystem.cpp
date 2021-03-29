#include "MovementSystem.h"

namespace MovementSystem {
float keypress_time = 0.0f;

void run(const Ref<Map> &map, entt::registry &registry, entt::entity entity,
         float delta_time) {
  if (keypress_time < KEY_PRESSED_DELAY) {
    keypress_time += delta_time;
    return;
  }

  keypress_time = 0.0f;

  auto &player = registry.get<PlayerComponent>(entity);

  auto &transform = registry.get<TransformComponent>(entity);

  auto &tile =
      map->get_next_tile(entity, transform.position, player.controller);

  if (tile->position == transform.position) {
    return;
  }

  transform.position = tile->position;

  if (registry.has<SpriteComponent>(entity)) {
    Direction sprite_direction{Direction::None};

    if (player.controller.Up) {
      sprite_direction = Direction::Up;
    } else if (player.controller.Down) {
      sprite_direction = Direction::Down;
    } else if (player.controller.Left) {
      sprite_direction = Direction::Left;
    } else if (player.controller.Right) {
      sprite_direction = Direction::Right;
    }

    auto depth = (tile->make_depth() - 1) + 2;

    registry.patch<SpriteComponent>(
        entity, [depth, sprite_direction](SpriteComponent &sprite) {
          sprite.depth = depth;
          sprite.direction = sprite_direction;
        });
  }
}

} // namespace MovementSystem
