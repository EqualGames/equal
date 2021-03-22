#ifndef EQUAL_SCENE_H
#define EQUAL_SCENE_H

#include "TextureLoader.h"
#include <entt/entity/registry.hpp>

struct Map;
struct Application;

struct Scene {
  Ref<entt::registry> registry{make_ref<entt::registry>()};
  TextureCache textures{};
  entt::entity player;
  entt::entity camera;
  Ref<Map> map{nullptr};
  Ref<Application> app{nullptr};

  virtual void init() = 0;
  virtual void update() = 0;
};

#endif // EQUAL_SCENE_H
