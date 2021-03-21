#ifndef EQUAL_DEMO_SCENE_H
#define EQUAL_DEMO_SCENE_H

#include "../components/Camera.h"
#include "../components/Player.h"
#include "../components/Sprite.h"
#include "../components/Transform.h"
#include "../core/Helpers.h"
#include "../core/Map.h"
#include "../core/Scene.h"
#include "../systems/CameraSystem.h"
#include "../systems/InputSystem.h"
#include "../systems/RendererSystem.h"
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <iostream>
#include <stdlib.h> // strtol
#include <string>
#include <vector>

struct DemoScene : Scene {
  entt::entity player;
  entt::entity camera;
  Map *map{nullptr};

  void init() override;

  void update() override;
};

#endif // EQUAL_DEMO_SCENE_H
