#ifndef EQUAL_APPLICATION_H
#define EQUAL_APPLICATION_H

#include "Scene.h"
#include "Types.h"
#include "imgui-SFML.h"
#include "imgui.h"
#include <SFML/Graphics.hpp>
#include <entt/entt.hpp>
#include <queue>
#include <string>

struct Application {
private:
  std::string title{"Equal Games"};
  Scene *scene{nullptr};

#ifdef DEBUG
  bool fullscreen{false};
#else
  bool fullscreen{true};
#endif

#ifdef DEV_TOOLS
  bool tools{false};
  float limit_fps = 120.0f;
  float min_fps{limit_fps};
  float avg_fps{limit_fps};
  float max_fps{-limit_fps};
  std::vector<float> frames;
  bool vsync{false};
#else
  bool vsync{true};
  float limit_fps = 60.0f;
#endif

public:
  Ref<sf::RenderWindow> window{nullptr};
  SizeFloat viewport_size{1024, 768};

  Application() = default;

  explicit Application(const Size &size, bool fullscreen = false)
      : viewport_size(size), fullscreen(fullscreen) {}

  bool init();

  void adjust_scale(const SizeFloat &screen_size);

  void set_scene(Scene *scene);

  int run();
};

#endif // EQUAL_APPLICATION_H
