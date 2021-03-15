#ifndef EQUAL_RENDERER_SYSTEM_H
#define EQUAL_RENDERER_SYSTEM_H

#include "../components/Camera.h"
#include "../components/Map.h"
#include "../components/Sprite.h"
#include "../components/Transform.h"
#include "../core/Helpers.h"
#include <SDL2/SDL.h>
#include <entt/entt.hpp>
#include <iostream>

void renderer_system(entt::registry &registry, SDL_Renderer *renderer,
                     const entt::entity &camera);
void render_sprite(entt::registry &registry, SDL_Renderer *renderer,
                   const Camera &camera, const entt::entity &entity);

#endif // EQUAL_RENDERER_SYSTEM_H
