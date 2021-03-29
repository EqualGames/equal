
#ifndef EQUAL_RENDERER_SYSTEM_H
#define EQUAL_RENDERER_SYSTEM_H

#include "../components/CameraComponent.h"
#include "../components/SpriteComponent.h"
#include "../components/TagComponent.h"
#include "../components/TransformComponent.h"
#include "../core/Logger.h"
#include "../core/Map.h"
#include "../core/Scene.h"
#include <SFML/Graphics.hpp>
#include <entt/entt.hpp>

namespace RendererSystem {

void run(Scene *scene, entt::registry &registry,
         const Ref<sf::RenderWindow> &renderer);

/**
 * Check the position is into camera bounds
 */
bool in_field_of_view(const Position &position, const Rect &camera_bounds);

void draw(const Ref<sf::RenderWindow> &renderer,
          const TransformFloat &transform, const SpriteComponent &sprite,
          const Ref<sf::Texture> &texture);

} // namespace RendererSystem

#endif // EQUAL_RENDERER_SYSTEM_H
