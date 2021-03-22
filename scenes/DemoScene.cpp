#include "DemoScene.h"

void reorder_sprites(entt::registry &registry) {
  registry.sort<SpriteComponent>(
      [](const SpriteComponent &left, const SpriteComponent &right) {
        return left.depth < right.depth;
      });
}

void DemoScene::init() {
  this->registry->on_construct<SpriteComponent>().connect<&reorder_sprites>();
  this->registry->on_update<SpriteComponent>().connect<&reorder_sprites>();

  this->textures.load<TextureLoader>(entt::hashed_string{"player"},
                                     this->app->renderer,
                                     "assets/NPC_test.png");

  {
    this->camera = this->registry->create();

    auto &cam = this->registry->emplace<CameraComponent>(this->camera);
    cam.position = Position{};
    cam.size = this->app->window_size;
  }

  {
    this->player = this->registry->create();

    auto &input = this->registry->emplace<PlayerComponent>(player);

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

    auto &transform = this->registry->emplace<TransformComponent>(this->player);
    transform.size = Size{32, 64};
    transform.position = Position{};

    auto &sprite = this->registry->emplace<SpriteComponent>(this->player);
    sprite.color = Color{255, 255, 255};

    sprite.textures.emplace_back(std::make_tuple(entt::hashed_string{"player"},
                                                 Position{}, Size{16, 32}));
  }

  {
    this->map = make_ref<Map>(this, "assets/map/demo.tmx",
                              "assets/map/objecttypes.xml");
    this->map->attach(*this->registry.get(), this->player);
  }
}

void DemoScene::update() {
  Tiled::Input::system(this);
  Tiled::Camera::system(this);
  Tiled::Renderer::system(this);
}
