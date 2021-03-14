#ifndef EQUAL_INPUT_H
#define EQUAL_INPUT_H

struct Input {
    int number{0};
    int speed{4};

    SDL_GameController *controller{nullptr};
    SDL_Joystick *joystick{nullptr};
    int32_t joystick_instance_id{-1};
};

#endif //EQUAL_INPUT_H
