#include "DemoScene.h"

void DemoScene::init() {
  {
    this->camera = this->app->registry.create();

    auto &cam = this->app->registry.emplace<Camera>(this->camera);
    cam.position = Position{};
    cam.size = app->window_size;
  }

  Position player_position{};

  {
    this->player = this->app->registry.create();

    auto &input = this->app->registry.emplace<Player>(player);

    if (SDL_NumJoysticks() > 0) {
      if (SDL_IsGameController(input.id)) {
        input.controller = SDL_GameControllerOpen(input.id);
        input.joystick = SDL_GameControllerGetJoystick(input.controller);
        input.joystick_instance_id = SDL_JoystickInstanceID(input.joystick);
      } else {
        input.joystick = SDL_JoystickOpen(input.id);
        input.joystick_instance_id = SDL_JoystickInstanceID(input.joystick);
        input.controller =
            SDL_GameControllerFromInstanceID(input.joystick_instance_id);
      }
    }

    auto &transform = this->app->registry.emplace<Transform>(this->player);
    transform.size = Size{32, 64};
    transform.position = player_position;

    auto &sprite = this->app->registry.emplace<Sprite>(this->player);
    sprite.color = Color{255, 255, 255};

    sprite.textures.emplace_back(std::make_tuple(
        load_texture(this->app->renderer, "assets/NPC_test.png"), Position{},
        Size{16, 32}));
  }

  {
    this->map = new Map(this->app->registry, "assets/map/demo.tmx",
                        "assets/map/objecttypes.xml", this->app->renderer);
    this->map->attach(this->app->registry, this->player);
  }
}

void DemoScene::update() {
  input_system(this->app, this->map, this->player);
  camera_system(this->app, this->camera, this->player);
  renderer_system(this->app,  this->map, this->camera);
}
