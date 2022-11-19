#pragma once

#include <string>

namespace eq {

    struct TagComponent {
        std::string name{};

        TagComponent() = default;
        TagComponent(const TagComponent &) = default;
    };

}// namespace eq
