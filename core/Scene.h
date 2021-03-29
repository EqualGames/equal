#ifndef EQUAL_SCENE_H
#define EQUAL_SCENE_H

#include "Texture.h"
#include "Types.h"
#include <SFML/Graphics/RenderWindow.hpp>

struct Map;
struct Application;

struct Scene {
  // ECS
  entt::registry registry;
  entt::entity player{entt::null};
  entt::entity camera{entt::null};

  // Data
  bool loading{true};
  Ref<Map> map{nullptr};
  Ref<Application> app{nullptr};
  TextureManager textures{};

  virtual ~Scene() {
    registry.clear();
    textures.clear();
    map = nullptr;
    app = nullptr;
  }

  virtual void init() = 0;
  virtual void event(const Event &event) = 0;
  virtual void update(float delta_time) = 0;
  virtual void draw(const Ref<sf::RenderWindow> &renderer) = 0;
};

#endif // EQUAL_SCENE_H
