#ifndef EQUAL_PLAYER_COMPONENT_H
#define EQUAL_PLAYER_COMPONENT_H

#include <SDL2/SDL.h>

struct PlayerComponent {
  int id{0};

  SDL_GameController *controller{nullptr};
  SDL_Joystick *joystick{nullptr};
  int32_t joystick_instance_id{-1};
};

#endif // EQUAL_PLAYER_COMPONENT_H
