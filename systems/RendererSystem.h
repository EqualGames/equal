#ifndef EQUAL_RENDERER_SYSTEM_H
#define EQUAL_RENDERER_SYSTEM_H

#include "../components/Camera.h"
#include "../components/Sprite.h"
#include "../components/Transform.h"
#include "../core/Application.h"
#include "../core/Helpers.h"
#include "../core/Map.h"
#include <SDL2/SDL.h>
#include <entt/entt.hpp>
#include <iostream>

void renderer_system(Application *app, const Map *map,
                     entt::entity camera_entity);

void render_sprite(entt::registry &registry, entt::entity &entity,
                   SDL_Renderer *renderer, const Camera &camera,
                   const Transform &transform, const Sprite &sprite,
                   const Size &map_tile_size);

bool in_camera_bound(const Map *map, const Position &position,
                     const Camera &camera);

bool is_renderable(const Map *map, const Transform &transform,
                   const Sprite &sprite);

#endif // EQUAL_RENDERER_SYSTEM_H
