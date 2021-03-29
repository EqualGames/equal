#ifndef EQUAL_PLAYER_COMPONENT_H
#define EQUAL_PLAYER_COMPONENT_H

struct ControllerState {
  bool Up{false};
  bool Down{false};
  bool Left{false};
  bool Right{false};
};

struct PlayerComponent {
  int id{0};

  ControllerState controller;
};

#endif // EQUAL_PLAYER_COMPONENT_H
