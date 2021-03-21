#ifndef EQUAL_APPLICATION_H
#define EQUAL_APPLICATION_H

#include "Scene.h"
#include "Timer.h"
#include "Types.h"
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_timer.h>
#include <entt/entt.hpp>
#include <string>

const int g_joystick_dead_zone = SDL_JOYSTICK_AXIS_MAX / 100 * 20;

struct Application {
  // ECS
  entt::registry registry;

  // Configuration
  Size window_size{800, 600};

  // Status
  Scene *scene{nullptr};
  DirectionalStatus direction;
  bool running{true};
  float deltaTime{0.0f};

  // SDL
  SDL_Window *window{nullptr};
  SDL_Event event{};
  SDL_Renderer *renderer{nullptr};

  Application() = default;

  Application(Scene *scene) : scene(scene) {}
  Application(Scene *scene, Size size) : scene(scene), window_size(size) {}
  Application(Size size) : window_size(size) {}

  bool init();

  void set_scene(Scene *scene);

  int run();

  void update_joystick();

  void update_keyboard();

  inline int normalize_axis(int val) {
    if (val > 0) {
      return 1;
    }

    if (val < 0) {
      return -1;
    }

    return 0;
  }
};

#endif // EQUAL_APPLICATION_H
