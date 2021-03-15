#ifndef EQUAL_SCENE_H
#define EQUAL_SCENE_H

#include <SDL2/SDL.h>
#include <entt/entt.hpp>

struct Application;

struct Scene {
  Application *app{nullptr};
  entt::registry registry;

  virtual void init(SDL_Renderer *renderer) = 0;

  virtual void update(SDL_Renderer *renderer, const SDL_Event &event,
                      const float &deltaTime) = 0;
};

#endif // EQUAL_SCENE_H
