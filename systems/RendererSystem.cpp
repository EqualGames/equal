#include "RendererSystem.h"

namespace RendererSystem {

void run(Scene *scene, entt::registry &registry,
         const Ref<sf::RenderWindow> &renderer) {
  const auto &camera = registry.get<CameraComponent>(scene->camera);

  const auto &entities =
      registry.view<const SpriteComponent, const TransformComponent,
                    const TagComponent>();

  SizeI32 map_tile_size{scene->map->tile_size};
  SizeI32 camera_size{camera.size};
  Rect camera_bound{
      camera.position.x - map_tile_size.w,
      camera.position.y - map_tile_size.h,
      camera.position.x + camera_size.w + map_tile_size.w,
      camera.position.y + camera_size.h + map_tile_size.h,
  };

  for (auto [entity, sprite, transform, tag] : entities.each()) {
    // ? Converts entity position to world position
    auto entity_position = Position{transform.position.x * map_tile_size.w,
                                    transform.position.y * map_tile_size.h};

    // ? Centers the entity on the screen based on camera
    TransformFloat entity_transform{entity_position - camera.position,
                                    transform.size};

    if (!in_field_of_view(entity_position, camera_bound)) {
      continue;
    }

    // ? Fix position of sprites with size more than the tile size
    if (entity_transform.size.w > map_tile_size.w) {
      entity_transform.position.x -=
          (entity_transform.size.w / map_tile_size.w - 1) *
          (map_tile_size.w / 2.0f);
    }

    if (entity_transform.size.h > map_tile_size.h) {
      entity_transform.position.y -=
          (entity_transform.size.h / map_tile_size.h) *
          (map_tile_size.h / 2.0f);
    }

    auto texture = scene->textures.get(sprite.texture_id);

    draw(renderer, entity_transform, sprite, texture);
  }
}

void draw(const Ref<sf::RenderWindow> &renderer,
          const TransformFloat &transform, const SpriteComponent &sprite,
          const Ref<sf::Texture> &texture) {
  sf::VertexArray quad(sf::Quads, 4);

  TransformFloat crop_rect{sprite.transform.position, sprite.transform.size};

  quad[0].texCoords = crop_rect.position.to_sfml();
  quad[1].texCoords = sf::Vector2f(crop_rect.position.x + crop_rect.size.w,
                                   crop_rect.position.y);
  quad[2].texCoords = sf::Vector2f(crop_rect.position.x + crop_rect.size.w,
                                   crop_rect.position.y + crop_rect.size.h);
  quad[3].texCoords = sf::Vector2f(crop_rect.position.x,
                                   crop_rect.position.y + crop_rect.size.h);

  quad[0].position = transform.position.to_sfml();
  quad[1].position = sf::Vector2f(transform.position.x + transform.size.w,
                                  transform.position.y);
  quad[2].position = sf::Vector2f(transform.position.x + transform.size.w,
                                  transform.position.y + transform.size.h);
  quad[3].position = sf::Vector2f(transform.position.x,
                                  transform.position.y + transform.size.h);

  sf::RenderStates state;
  state.texture = texture.get();

  renderer->draw(quad, state);
}

bool in_field_of_view(const Position &position, const Rect &camera_bounds) {
  return camera_bounds.left <= position.x && camera_bounds.top <= position.y &&
         camera_bounds.right >= position.x &&
         camera_bounds.bottom >= position.y;
}

} // namespace RendererSystem
