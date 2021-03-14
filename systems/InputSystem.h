#ifndef EQUAL_INPUT_SYSTEM_H
#define EQUAL_INPUT_SYSTEM_H

#include <entt/entt.hpp>
#include <SDL2/SDL.h>
#include <SDL2/SDL_gamecontroller.h>
#include "../core/Types.h"
#include "../components/Input.h"
#include "../components/Transform.h"
#include "../components/Camera.h"

const int JOYSTICK_DEAD_ZONE = 8000;

extern uint8_t g_movement_direction;

void input_system(entt::registry &registry, SDL_Event &event);

double normalize_axis(int val);

#endif //EQUAL_INPUT_SYSTEM_H
