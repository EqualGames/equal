#ifndef EQUAL_INPUT_H
#define EQUAL_INPUT_H

#include <SDL2/SDL.h>

struct Input {
  int number{0};
  int speed{1};

  SDL_GameController *controller{nullptr};
  SDL_Joystick *joystick{nullptr};
  int32_t joystick_instance_id{-1};
};

#endif // EQUAL_INPUT_H
