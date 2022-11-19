#pragma once

#include "../core/Entity.h"
#include "../core/Types.h"
#include "../export.h"

namespace eq::InputSystem {

    EQ_EXPORT void run(const Event &event, Entity &entity);

}// namespace eq::InputSystem
