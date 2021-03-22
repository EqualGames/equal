#include "InputSystem.h"

namespace Tiled::Input {

float keypress_time = 0.0f;

void system(Scene *scene) {
  if (keypress_time < KEY_PRESSED_DELAY) {
    keypress_time += scene->app->deltaTime;
    return;
  }

  keypress_time = 0.0f;

  bool some_key_active =
      scene->app->direction.up || scene->app->direction.down ||
      scene->app->direction.left || scene->app->direction.right;

  if (some_key_active) {
    const auto &transform =
        scene->registry->get<TransformComponent>(scene->player);

    auto position = scene->map->get_next_tile(scene->player, transform.position,
                                              scene->app->direction);
    auto tile = scene->map->get_tile(position);

    scene->registry->patch<SpriteComponent>(
        scene->player, [tile, scene](SpriteComponent &sprite) {
          if (scene->app->direction.up) {
            sprite.direction = Direction::Up;
          } else if (scene->app->direction.down) {
            sprite.direction = Direction::Down;
          } else if (scene->app->direction.left) {
            sprite.direction = Direction::Left;
          } else if (scene->app->direction.right) {
            sprite.direction = Direction::Right;
          }

          sprite.depth = Map::make_depth(tile, ThingOrder::CREATURE);
        });

    scene->registry->patch<TransformComponent>(
        scene->player, [position](TransformComponent &transform) {
          transform.position = position;
        });
  }
}
} // namespace Tiled::Input
