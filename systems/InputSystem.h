#ifndef EQUAL_INPUT_SYSTEM_H
#define EQUAL_INPUT_SYSTEM_H

#include "../components/Camera.h"
#include "../components/Player.h"
#include "../components/Sprite.h"
#include "../components/Transform.h"
#include "../core/Application.h"
#include "../core/Map.h"
#include "../core/Types.h"
#include <SDL2/SDL.h>
#include <SDL2/SDL_gamecontroller.h>
#include <entt/entt.hpp>

const float g_keypress_delay = 0.032f;

void input_system(Application *app, Map *map, entt::entity player_entity);

#endif // EQUAL_INPUT_SYSTEM_H
