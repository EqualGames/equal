#ifndef EQUAL_DEMO_SCENE_H
#define EQUAL_DEMO_SCENE_H

#include "../components/Camera.h"
#include "../components/Input.h"
#include "../components/Map.h"
#include "../components/Sprite.h"
#include "../components/Transform.h"
#include "../core/Application.h"
#include "../core/Helpers.h"
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
  entt::entity map;

  void init(SDL_Renderer *renderer) override;

  void update(SDL_Renderer *renderer, const SDL_Event &event,
              const float &deltaTime) override;
};

#endif // EQUAL_DEMO_SCENE_H
