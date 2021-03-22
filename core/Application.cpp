#include "Application.h"

bool Application::init() {

  if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_JOYSTICK) < 0) {
    printf("SDL could not initialize! SDL_Error: %s\n", SDL_GetError());
    return false;
  }

  this->window = SDL_CreateWindow("Equal Games", SDL_WINDOWPOS_UNDEFINED,
                                  SDL_WINDOWPOS_UNDEFINED, this->window_size.w,
                                  this->window_size.h, SDL_WINDOW_SHOWN);

  if (window == nullptr) {
    printf("Window could not be created! SDL_Error: %s\n", SDL_GetError());
    return false;
  }

  if (fullscreen) {
    SDL_SetWindowFullscreen(this->window, SDL_WINDOW_FULLSCREEN_DESKTOP);
  }

  this->renderer = SDL_CreateRenderer(
      this->window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);

  if (this->renderer == nullptr) {
    printf("Renderer could not be created! SDL Error: %s\n", SDL_GetError());
    return false;
  }

  SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "nearest");
  SDL_SetHint(SDL_HINT_RENDER_LOGICAL_SIZE_MODE, "letterbox");

  if (SDL_RenderSetLogicalSize(this->renderer, this->window_size.w,
                               this->window_size.h)) {
    printf("SDL could not set the render logical size! SDL_Error: %s\n",
           SDL_GetError());
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
  if (this->scene) {
    this->scene->registry->clear();
    this->scene->textures.clear();
  }
  this->scene = p_scene;
  this->scene->app = (Ref<Application>)this;
  this->scene->init();
}

const float SCREEN_TICKS_PER_FRAME = 0.016f;

int Application::run() {
  if (this->scene == nullptr) {
    printf("Invalid scene");
    return 1;
  }

  Timer timer;
#ifdef DEBUG_FPS
  float minFPS = 60.0f;
  float maxFPS = -60.0f;
#endif

  while (this->running) {
    timer.start();

    while (SDL_PollEvent(&this->event) != 0) {
      if (event.type == SDL_QUIT ||
          event.type == SDL_KEYDOWN && event.key.keysym.sym == SDLK_ESCAPE) {
        this->running = false;
      } else {
        this->update_joystick();
        this->update_keyboard();
      }
    }

    SDL_SetRenderDrawColor(this->renderer, 0, 0, 0, 0);
    SDL_RenderClear(this->renderer);

    scene->update();

    SDL_RenderPresent(this->renderer);

    this->deltaTime = timer.get_ticks() / 1000.0f;

    if (this->deltaTime < SCREEN_TICKS_PER_FRAME) {
      float diff = SCREEN_TICKS_PER_FRAME - this->deltaTime;

      SDL_Delay(diff * 1000.0f);
    }

#ifdef DEBUG_FPS
    float fps = 1000.0f / timer.get_ticks();
    if (fps < minFPS) {
      minFPS = fps;
    }

    if (fps > maxFPS) {
      maxFPS = fps;
    }
#endif
  }

#ifdef DEBUG_FPS
  printf("FPS: min %.0f  max %.0f\n", minFPS, maxFPS);
#endif

  this->scene = nullptr;
  this->renderer = nullptr;
  SDL_DestroyWindow(this->window);
  this->window = nullptr;
  SDL_Quit();

  return 0;
}

void Application::update_joystick() {
  if (event.type != SDL_JOYAXISMOTION) {
    return;
  }

  if (event.jaxis.value > g_joystick_dead_zone ||
      event.jaxis.value < -g_joystick_dead_zone) {
    auto value = normalize_axis(event.jaxis.value);

    if (event.jaxis.axis == SDL_CONTROLLER_AXIS_LEFTY) {
      if (value < 0) {
        direction.up = true;
      }

      if (value > 0) {
        direction.down = true;
      }
    }

    if (event.jaxis.axis == SDL_CONTROLLER_AXIS_LEFTX) {
      if (value < 0) {
        direction.left = true;
      }

      if (value > 0) {
        direction.right = true;
      }
    }
  } else {
    if (event.jaxis.axis == SDL_CONTROLLER_AXIS_LEFTY) {
      direction.up = false;
      direction.down = false;
    }

    if (event.jaxis.axis == SDL_CONTROLLER_AXIS_LEFTX) {
      direction.left = false;
      direction.right = false;
    }
  }
}

void Application::update_keyboard() {
  if (event.type != SDL_KEYDOWN && event.type != SDL_KEYUP) {
    return;
  }

  auto isUp = event.key.keysym.scancode == SDL_SCANCODE_UP;
  auto isDown = event.key.keysym.scancode == SDL_SCANCODE_DOWN;
  auto isLeft = event.key.keysym.scancode == SDL_SCANCODE_LEFT;
  auto isRight = event.key.keysym.scancode == SDL_SCANCODE_RIGHT;

  if (event.type == SDL_KEYDOWN) {
    if (isUp) {
      direction.up = true;
    }

    if (isDown) {
      direction.down = true;
    }

    if (isLeft) {
      direction.left = true;
    }

    if (isRight) {
      direction.right = true;
    }
  }

  if (event.type == SDL_KEYUP) {
    if (isUp) {
      direction.up = false;
    }

    if (isDown) {
      direction.down = false;
    }

    if (isLeft) {
      direction.left = false;
    }

    if (isRight) {
      direction.right = false;
    }
  }
}
