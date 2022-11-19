#pragma once

#include "../core/Texture.h"
#include "../core/Types.h"
#include <string>
#include <tuple>
#include <vector>

namespace eq {

    struct SpriteComponent {
        typedef enum {
            BORDER,
            FILL,
            FULL,
        } RenderMode;

        int depth{0};
        std::string texture_id{};
        Transform transform{};
        Color color{};
        RenderMode render_type{RenderMode::FULL};
        Direction direction{Direction::Down};

        SpriteComponent() = default;
        SpriteComponent(const SpriteComponent &) = default;
    };

}// namespace eq
