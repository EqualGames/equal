#ifndef EQUAL_INPUT_SYSTEM_H
#define EQUAL_INPUT_SYSTEM_H

#include "../components/PlayerComponent.h"
#include "../core/Scene.h"
#include "../core/Types.h"

namespace InputSystem {

void run(entt::registry &registry, entt::entity entity, const Event &event);

} // namespace Tiled::Input

#endif // EQUAL_INPUT_SYSTEM_H
