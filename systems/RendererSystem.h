
#ifndef EQUAL_RENDERER_SYSTEM_H
#define EQUAL_RENDERER_SYSTEM_H

#include "../components/CameraComponent.h"
#include "../components/SpriteComponent.h"
#include "../components/TransformComponent.h"
#include "../core/Map.h"
#include "../core/Scene.h"
#include <SDL2/SDL.h>
#include <entt/entt.hpp>
#include <iostream>

namespace Tiled::Renderer {

void system(Scene *scene);

bool in_field_of_view(const Ref<Map> &map, const Position &position,
                      const CameraComponent &camera,
                      const TransformComponent &player);

bool in_render_range(const Ref<Map> &map, const TransformComponent &transform,
                     const SpriteComponent &sprite);

void draw(SDL_Renderer *renderer, const TextureCache &textures,
          const CameraComponent &camera, const TransformComponent &transform,
          const SpriteComponent &sprite, const Size &map_tile_size);
} // namespace Tiled::Renderer

#endif // EQUAL_RENDERER_SYSTEM_H
