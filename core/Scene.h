#ifndef EQUAL_SCENE_H
#define EQUAL_SCENE_H

#include <SDL2/SDL.h>
#include <entt/entt.hpp>

struct Application;

struct Scene {
  Application *app{nullptr};

  virtual void init() = 0;
  virtual void update() = 0;
};

#endif // EQUAL_SCENE_H
