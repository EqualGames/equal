#include "RendererSystem.h"

namespace Tiled::Renderer {
void system(Scene *scene) {
  const auto &camera = scene->registry->get<CameraComponent>(scene->camera);
  const auto &player = scene->registry->get<TransformComponent>(scene->player);
  auto entities =
      scene->registry->view<const SpriteComponent, const TransformComponent>();

  for (auto [entity, sprite, transform] : entities.each()) {
    bool need_to_render =
        in_field_of_view(scene->map, transform.position, camera, player) &&
        in_render_range(scene->map, transform, sprite);

    if (need_to_render) {
      draw(scene->app->renderer, scene->textures, camera, transform, sprite,
           scene->map->tile_size);
    }
  }
}

bool in_field_of_view(const Ref<Map> &map, const Position &position,
                      const CameraComponent &camera,
                      const TransformComponent &player) {

  if (player.position.z > position.z) {
    return false;
  }

  return position.x >= camera.position.x - map->tile_size.w &&
         position.y >= camera.position.y - map->tile_size.h &&
         position.x <= camera.position.x + camera.size.w &&
         position.y <= camera.position.y + camera.size.h;
}

bool in_render_range(const Ref<Map> &map, const TransformComponent &transform,
                     const SpriteComponent &sprite) {
  int depth = map->get_depth(sprite.depth, transform.position);

  return depth < Map::MAX_TILE_VISIBLE_ENTITIES;
}

void draw(SDL_Renderer *renderer, const TextureCache &textures,
          const CameraComponent &camera, const TransformComponent &transform,
          const SpriteComponent &sprite, const Size &map_tile_size) {
  SDL_Rect target_rect{
      transform.position.x - camera.position.x,
      transform.position.y - camera.position.y,
      transform.size.w,
      transform.size.h,
  };

  if (target_rect.w > map_tile_size.w) {
    target_rect.x -=
        ((target_rect.w / map_tile_size.w) - 1) * (map_tile_size.w / 2);
  }

  if (target_rect.h > map_tile_size.h) {
    target_rect.y -= (target_rect.h / map_tile_size.h) * (map_tile_size.h / 2);
  }

  if (sprite.textures.empty()) {
    const auto &color = sprite.color;

    SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, color.a);
    SDL_RenderFillRect(renderer, &target_rect);

    return;
  }

  auto [texture_id, crop_position, crop_size] = sprite.textures.at(0);

  if (!textures.contains(texture_id)) {
    printf("Texture not found\n");
    return;
  }

  auto handle = textures.handle(texture_id);
  auto &texture = handle.get();

  SDL_Rect texture_rect{
      crop_position.x,
      crop_position.y,
      crop_size.w,
      crop_size.h,
  };

  SDL_RenderCopy(renderer, texture.data.get(), &texture_rect, &target_rect);
}
} // namespace Tiled::Renderer
