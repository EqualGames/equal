#ifndef EQUAL_DEMO_SCENE_H
#define EQUAL_DEMO_SCENE_H

#include "../components/CameraComponent.h"
#include "../components/PlayerComponent.h"
#include "../components/SpriteComponent.h"
#include "../components/TagComponent.h"
#include "../components/TransformComponent.h"
#include "../core/Application.h"
#include "../core/Logger.h"
#include "../core/Map.h"
#include "../core/Scene.h"
#include "../systems/CameraSystem.h"
#include "../systems/InputSystem.h"
#include "../systems/MovementSystem.h"
#include "../systems/RendererSystem.h"

using namespace entt::literals;

struct DemoScene : Scene {

  ~DemoScene() {
    registry.on_construct<SpriteComponent>()
        .disconnect<&DemoScene::on_sprite_update>(this);
    registry.on_update<SpriteComponent>()
        .disconnect<&DemoScene::on_sprite_update>(this);
  }

  void init() override;

  void event(const Event &event) override;

  void update(float delta_time) override;

  void draw(const Ref<sf::RenderWindow> &renderer) override;

  void on_sprite_update(entt::registry &registry, entt::entity entity);
};

#endif // EQUAL_DEMO_SCENE_H
