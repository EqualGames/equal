#ifndef EQUAL_DEMO_SCENE_H
#define EQUAL_DEMO_SCENE_H

#include <iostream>
#include <stdlib.h> // strtol
#include <string>
#include <vector>
#include <pugixml.hpp>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include "../core/Application.h"
#include "../core/Scene.h"
#include "../core/Helpers.h"
#include "../components/Map.h"
#include "../components/Transform.h"
#include "../components/Sprite.h"
#include "../components/Input.h"
#include "../components/Camera.h"
#include "../systems/RendererSystem.h"
#include "../systems/InputSystem.h"
#include "../systems/CameraSystem.h"

struct DemoScene : Scene {
    entt::entity player;
    entt::entity camera;
    entt::entity map;

    void init(SDL_Renderer *renderer) override;

    void update(SDL_Renderer *renderer, SDL_Event &event) override;
};

#endif //EQUAL_DEMO_SCENE_H