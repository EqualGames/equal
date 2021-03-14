#ifndef EQUAL_SCENE_H
#define EQUAL_SCENE_H

#include <entt/entt.hpp>
#include <SDL2/SDL.h>

struct Application;

struct Scene {
    Application *app{nullptr};
    entt::registry registry;

    virtual void init(SDL_Renderer *renderer) = 0;

    virtual void update(SDL_Renderer *renderer, SDL_Event &event) = 0;
};

#endif //EQUAL_SCENE_H
