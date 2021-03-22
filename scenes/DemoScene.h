#ifndef EQUAL_DEMO_SCENE_H
#define EQUAL_DEMO_SCENE_H

#include "../components/CameraComponent.h"
#include "../components/PlayerComponent.h"
#include "../components/SpriteComponent.h"
#include "../components/TransformComponent.h"
#include "../core/Application.h"
#include "../core/Scene.h"
#include "../systems/CameraSystem.h"
#include "../systems/InputSystem.h"
#include "../systems/RendererSystem.h"
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <cstdlib> // strtol
#include <iostream>
#include <string>
#include <vector>

struct DemoScene : Scene {

  void init() override;

  void update() override;
};

#endif // EQUAL_DEMO_SCENE_H
