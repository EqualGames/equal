#include "Application.h"

bool Application::init() {
  if (SDL_Init(SDL_INIT_EVERYTHING) < 0) {
    printf("SDL could not initialize! SDL_Error: %s\n", SDL_GetError());
    return false;
  }

  if (!SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "0")) {
    printf("Warning: Linear texture filtering not enabled!");
  }

  this->window = SDL_CreateWindow("Equal Games", SDL_WINDOWPOS_CENTERED,
                                  SDL_WINDOWPOS_CENTERED, this->window_size.w,
                                  this->window_size.h, SDL_WINDOW_SHOWN);

  if (window == nullptr) {
    printf("Window could not be created! SDL_Error: %s\n", SDL_GetError());
    return false;
  }

  this->renderer = SDL_CreateRenderer(
      this->window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);

  if (this->renderer == nullptr) {
    printf("Renderer could not be created! SDL Error: %s\n", SDL_GetError());
    return false;
  }

  int imgFlags = IMG_INIT_PNG;
  if (!(IMG_Init(imgFlags) & imgFlags)) {
    printf("SDL_image could not initialize! SDL_image Error: %s\n",
           IMG_GetError());
    return false;
  }

  return true;
}

void Application::set_scene(Scene *p_scene) {
  this->scene = p_scene;
  this->scene->app = this;
  this->scene->init(this->renderer);
}

const float SCREEN_TICKS_PER_FRAME = 0.016f;

int Application::run() {
  if (this->scene == nullptr) {
    printf("Invalid scene");
    return 1;
  }

  LTimer timer;
  float deltaTime{0.0f};

  while (this->running) {
    timer.start();

    while (SDL_PollEvent(&event) != 0) {
      if (event.type == SDL_QUIT ||
          event.type == SDL_KEYDOWN && event.key.keysym.sym == SDLK_ESCAPE) {
        this->running = false;
      }
    }

    SDL_SetRenderDrawColor(this->renderer, 0, 0, 0, 0);
    SDL_RenderClear(this->renderer);

    scene->update(this->renderer, this->event, deltaTime);

    SDL_RenderPresent(this->renderer);

    deltaTime = timer.getTicks() / 1000.0f;

    if (deltaTime < SCREEN_TICKS_PER_FRAME) {
      float diff = SCREEN_TICKS_PER_FRAME - deltaTime;

      SDL_Delay(diff * 1000.0f);
    }
  }

  this->scene = nullptr;
  this->renderer = nullptr;
  SDL_DestroyWindow(window);
  this->window = nullptr;

  SDL_Quit();

  return 0;
}

LTimer::LTimer() {
  // Initialize the variables
  mStartTicks = 0;
  mPausedTicks = 0;

  mPaused = false;
  mStarted = false;
}

void LTimer::start() {
  // Start the timer
  mStarted = true;

  // Unpause the timer
  mPaused = false;

  // Get the current clock time
  mStartTicks = SDL_GetTicks();
  mPausedTicks = 0;
}

void LTimer::stop() {
  // Stop the timer
  mStarted = false;

  // Unpause the timer
  mPaused = false;

  // Clear tick variables
  mStartTicks = 0;
  mPausedTicks = 0;
}

void LTimer::pause() {
  // If the timer is running and isn't already paused
  if (mStarted && !mPaused) {
    // Pause the timer
    mPaused = true;

    // Calculate the paused ticks
    mPausedTicks = SDL_GetTicks() - mStartTicks;
    mStartTicks = 0;
  }
}

void LTimer::unpause() {
  // If the timer is running and paused
  if (mStarted && mPaused) {
    // Unpause the timer
    mPaused = false;

    // Reset the starting ticks
    mStartTicks = SDL_GetTicks() - mPausedTicks;

    // Reset the paused ticks
    mPausedTicks = 0;
  }
}

Uint32 LTimer::getTicks() {
  // The actual timer time
  Uint32 time = 0;

  // If the timer is running
  if (mStarted) {
    // If the timer is paused
    if (mPaused) {
      // Return the number of ticks when the timer was paused
      time = mPausedTicks;
    } else {
      // Return the current time minus the start time
      time = SDL_GetTicks() - mStartTicks;
    }
  }

  return time;
}

bool LTimer::isStarted() {
  // Timer is running and paused or unpaused
  return mStarted;
}

bool LTimer::isPaused() {
  // Timer is running and paused
  return mPaused && mStarted;
}
