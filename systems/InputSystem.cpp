#include "InputSystem.h"

float keypress_time = 0.0f;
void input_system(Application *app, Map *map, entt::entity player_entity) {

  if (keypress_time < g_keypress_delay) {
    keypress_time += app->deltaTime;
    return;
  }

  keypress_time = 0.0f;

  bool some_key_active = app->direction.up || app->direction.down ||
                         app->direction.left || app->direction.right;

  if (some_key_active) {
    auto [player, transform, sprite] =
        app->registry.get<Player, Transform, Sprite>(player_entity);

    if (app->direction.up) {
      sprite.direction = Direction::Up;
    } else if (app->direction.down) {
      sprite.direction = Direction::Down;
    } else if (app->direction.left) {
      sprite.direction = Direction::Left;
    } else if (app->direction.right) {
      sprite.direction = Direction::Right;
    }

#ifdef DEBUG_INPUT_SYSTEM
    Position last_position = transform.position;
#endif

    auto position =
        map->get_next_tile(player_entity, transform.position, app->direction);
    auto tile = map->get_tile(position);

    transform.position = position;
    sprite.depth = Map::make_depth(tile, ThingOrder::CREATURE);

#ifdef DEBUG_INPUT_SYSTEM
    printf("InputSystem <- Direction(%i %i) (%i %i)\n", direction.up,
           direction.down, direction.left, direction.right);

    printf("InputSystem <- from (%i %i) to (%i %i)\n", last_position.x,
           last_position.y, transform.position.x, transform.position.y);
#endif
  }
}

