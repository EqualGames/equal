#ifndef EQUAL_INPUT_SYSTEM_H
#define EQUAL_INPUT_SYSTEM_H

#include "../components/CameraComponent.h"
#include "../components/PlayerComponent.h"
#include "../components/SpriteComponent.h"
#include "../components/TransformComponent.h"
#include "../core/Map.h"
#include "../core/Scene.h"
#include "../core/Types.h"
#include <SDL2/SDL.h>
#include <SDL2/SDL_gamecontroller.h>
#include <entt/entt.hpp>

namespace Tiled::Input {

const float KEY_PRESSED_DELAY = 0.032f;

void system(Scene *scene);

} // namespace Tiled::Input

#endif // EQUAL_INPUT_SYSTEM_H
