#ifndef EQUAL_INPUT_SYSTEM_H
#define EQUAL_INPUT_SYSTEM_H

#include "../components/Camera.h"
#include "../components/Input.h"
#include "../components/Map.h"
#include "../components/Transform.h"
#include "../core/Types.h"
#include <SDL2/SDL.h>
#include <SDL2/SDL_gamecontroller.h>
#include <entt/entt.hpp>

const int JOYSTICK_DEAD_ZONE = 8000;

extern uint32_t g_movement_direction;
extern float g_keypress_time;

void input_system(entt::registry &registry, const SDL_Event &event,
                  const float &deltaTime, const entt::entity &map_entity);

double normalize_axis(int val);

#endif // EQUAL_INPUT_SYSTEM_H
