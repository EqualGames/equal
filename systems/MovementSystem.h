#ifndef EQUAL_MOVEMENTSYSTEM_H
#define EQUAL_MOVEMENTSYSTEM_H

#include "../components/PlayerComponent.h"
#include "../components/SpriteComponent.h"
#include "../components/TransformComponent.h"
#include "../core/Map.h"
#include "../core/Scene.h"

namespace MovementSystem {

const float KEY_PRESSED_DELAY = 0.032f;

void run(const Ref<Map> &map, entt::registry &registry, entt::entity entity,
         float delta_time);

}; // namespace MovementSystem

#endif // EQUAL_MOVEMENTSYSTEM_H
