#pragma once

namespace eq {

    struct ControllerState {
        bool Up{false};
        bool Down{false};
        bool Left{false};
        bool Right{false};
    };

    struct PlayerComponent {
        int id{0};

        ControllerState controller{};
    };

}// namespace eq
