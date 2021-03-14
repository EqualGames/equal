#ifndef EQUAL_RENDERER_SYSTEM_H
#define EQUAL_RENDERER_SYSTEM_H

#include <iostream>
#include <entt/entt.hpp>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include "../components/Map.h"
#include "../components/Transform.h"
#include "../components/Sprite.h"
#include "../components/Camera.h"

SDL_Texture *load_texture(SDL_Renderer *renderer, const std::string &path);

void renderer_system(entt::registry &registry, SDL_Renderer *renderer, entt::entity &camera);

#endif //EQUAL_RENDERER_SYSTEM_H
