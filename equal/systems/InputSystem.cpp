#include "InputSystem.h"
#include "../components/PlayerComponent.h"

namespace eq::InputSystem {

    void run(const Event &event, Entity &entity) {
        auto isUp = event.key.code == Keyboard::Up;
        auto isDown = event.key.code == Keyboard::Down;
        auto isLeft = event.key.code == Keyboard::Left;
        auto isRight = event.key.code == Keyboard::Right;

        auto &player = entity.get_component<PlayerComponent>();

        if (event.type == Event::KeyPressed) {
            if (isUp) {
                player.controller.Up = true;
            }

            if (isDown) {
                player.controller.Down = true;
            }

            if (isLeft) {
                player.controller.Left = true;
            }

            if (isRight) {
                player.controller.Right = true;
            }
        }

        if (event.type == Event::KeyReleased) {
            if (isUp) {
                player.controller.Up = false;
            }

            if (isDown) {
                player.controller.Down = false;
            }

            if (isLeft) {
                player.controller.Left = false;
            }

            if (isRight) {
                player.controller.Right = false;
            }
        }
    }

}// namespace eq::InputSystem
