#include "DemoScene.h"

void DemoScene::init(SDL_Renderer *renderer) {
  {
    this->camera = this->registry.create();

    auto &cam = this->registry.emplace<Camera>(this->camera);
    cam.position = Position{0, 0};
    cam.size = app->window_size;
  }

  {
    this->player = this->registry.create();

    auto &input = this->registry.emplace<Input>(player);

    if (SDL_NumJoysticks() > 0) {
      if (SDL_IsGameController(input.number)) {
        input.controller = SDL_GameControllerOpen(input.number);
        input.joystick = SDL_GameControllerGetJoystick(input.controller);
        input.joystick_instance_id = SDL_JoystickInstanceID(input.joystick);
      } else {
        input.joystick = SDL_JoystickOpen(input.number);
        input.joystick_instance_id = SDL_JoystickInstanceID(input.joystick);
        input.controller =
            SDL_GameControllerFromInstanceID(input.joystick_instance_id);
      }
    }

    auto &transform = this->registry.emplace<Transform>(this->player);
    transform.position = Position{0, 0};
    transform.size = Size{32, 64};

    auto &sprite = this->registry.emplace<Sprite>(this->player);
    sprite.color = Color{255, 255, 255};

    sprite.textures.emplace_back(
        std::make_tuple(load_texture(renderer, "assets/NPC_test.png"),
                        Position{0, 0}, Size{16, 32}));
  }

  {
    this->map = this->registry.create();

    auto tilemap =
        make_map("assets/map/demo.tmx", "assets/map/objecttypes.xml", renderer);

    Thing *thing = new Thing{};
    thing->id = this->player;
    thing->flags = TileFlag::ENTITY;

    const auto transform = this->registry.get<Transform>(this->player);

    tilemap.add_thing(transform.position, 0, 1, thing);

    this->registry.emplace<Map>(this->map, tilemap);
  }
}

void DemoScene::update(SDL_Renderer *renderer, const SDL_Event &event,
                       const float &deltaTime) {
  input_system(this->registry, event, deltaTime, this->map);
  camera_system(this->registry, this->camera, this->player);
  renderer_system(this->registry, renderer, this->camera);
}
