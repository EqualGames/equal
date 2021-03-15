#include "InputSystem.h"

uint32_t g_movement_direction = 0;
float g_keypress_time = 0.0f;

void input_system(entt::registry &registry, const SDL_Event &event,
                  const float &deltaTime, const entt::entity &map_entity) {

  if (g_keypress_time < 0.025f) {
    g_keypress_time += deltaTime;
    return;
  }

  g_keypress_time = 0.0f;

  if (event.type == SDL_JOYAXISMOTION) {
    if (event.jaxis.value > JOYSTICK_DEAD_ZONE ||
        event.jaxis.value < -JOYSTICK_DEAD_ZONE) {
      auto value = normalize_axis(event.jaxis.value);

      if (event.jaxis.axis == SDL_CONTROLLER_AXIS_LEFTY) {
        if (value < 0) {
          g_movement_direction |= Direction::Up;

          if (g_movement_direction & Direction::Down)
            g_movement_direction &= ~Direction::Down;
        }

        if (value > 0) {
          g_movement_direction |= Direction::Down;

          if (g_movement_direction & Direction::Up)
            g_movement_direction &= ~Direction::Up;
        }
      }
      if (event.jaxis.axis == SDL_CONTROLLER_AXIS_LEFTX) {
        if (value < 0) {
          g_movement_direction |= Direction::Left;

          if (g_movement_direction & Direction::Right)
            g_movement_direction &= ~Direction::Right;
        }

        if (value > 0) {
          g_movement_direction |= Direction::Right;

          if (g_movement_direction & Direction::Left)
            g_movement_direction &= ~Direction::Left;
        }
      }
    } else {
      if (event.jaxis.axis == SDL_CONTROLLER_AXIS_LEFTY) {
        g_movement_direction &= ~Direction::Up;
        g_movement_direction &= ~Direction::Down;
      }

      if (event.jaxis.axis == SDL_CONTROLLER_AXIS_LEFTX) {
        g_movement_direction &= ~Direction::Left;
        g_movement_direction &= ~Direction::Right;
      }
    }
  } else if (event.type == SDL_KEYDOWN || event.type == SDL_KEYUP) {
    auto isUp = event.key.keysym.scancode == SDL_SCANCODE_UP;
    auto isDown = event.key.keysym.scancode == SDL_SCANCODE_DOWN;
    auto isLeft = event.key.keysym.scancode == SDL_SCANCODE_LEFT;
    auto isRight = event.key.keysym.scancode == SDL_SCANCODE_RIGHT;

    if (event.key.state == SDL_PRESSED) {
      if (isUp) {
        g_movement_direction |= Direction::Up;

        if (g_movement_direction & Direction::Down) {
          g_movement_direction &= ~Direction::Down;
        }
      }

      if (isDown) {
        g_movement_direction |= Direction::Down;

        if (g_movement_direction & Direction::Up) {
          g_movement_direction &= ~Direction::Up;
        }
      }

      if (isLeft) {
        g_movement_direction |= Direction::Left;

        if (g_movement_direction & Direction::Right) {
          g_movement_direction &= ~Direction::Right;
        }
      }

      if (isRight) {
        g_movement_direction |= Direction::Right;

        if (g_movement_direction & Direction::Left) {
          g_movement_direction &= ~Direction::Left;
        }
      }
    }

    if (event.key.state == SDL_RELEASED) {
      if (isUp && g_movement_direction & Direction::Up) {
        g_movement_direction &= ~Direction::Up;
      }

      if (isDown && g_movement_direction & Direction::Down) {
        g_movement_direction &= ~Direction::Down;
      }

      if (isLeft && g_movement_direction & Direction::Left) {
        g_movement_direction &= ~Direction::Left;
      }

      if (isRight && g_movement_direction & Direction::Right) {
        g_movement_direction &= ~Direction::Right;
      }
    }
  }

  if (g_movement_direction != Direction::None) {
    auto view = registry.view<const Input, Transform>();
    auto map = registry.get<Map>(map_entity);

    for (auto [entity, input, transform] : view.each()) {
      transform.position = map.get_next_tile(entity, transform.position,
                                             g_movement_direction, 0);
    }
  }
}

double normalize_axis(int val) {
  if (val > 0)
    return 1;
  else if (val < 0)
    return -1;
  else
    return 0;
}
