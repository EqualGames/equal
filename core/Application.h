#ifndef EQUAL_APPLICATION_H
#define EQUAL_APPLICATION_H

#include "Scene.h"
#include "Types.h"
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_timer.h>

struct Application {
  Scene *scene{nullptr};
  bool running{true};
  Size window_size{800, 600};

  SDL_Window *window{nullptr};
  SDL_Event event{};
  SDL_Renderer *renderer{nullptr};

  Application() = default;

  explicit Application(Scene *scene) : scene(scene) {}

  bool init();

  void set_scene(Scene *scene);

  int run();
};

class LTimer {
public:
  // Initializes variables
  LTimer();

  // The various clock actions
  void start();
  void stop();
  void pause();
  void unpause();

  // Gets the timer's time
  Uint32 getTicks();

  // Checks the status of the timer
  bool isStarted();
  bool isPaused();

private:
  // The clock time when the timer started
  Uint32 mStartTicks;

  // The ticks stored when the timer was paused
  Uint32 mPausedTicks;

  // The timer status
  bool mPaused;
  bool mStarted;
};

#endif // EQUAL_APPLICATION_H
