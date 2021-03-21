#include "RendererSystem.h"

void renderer_system(Application *app, const Map *map,
                     entt::entity camera_entity) {

  app->registry.sort<Sprite>([](const Sprite &left, const Sprite &right) {
    return left.depth < right.depth;
  });

  app->registry.sort<Transform>(
      [](const Transform &left, const Transform &right) {
        return left.position.z < right.position.z;
      });

  const auto &camera = app->registry.get<Camera>(camera_entity);
  auto entities = app->registry.view<const Sprite, const Transform>();

  for (auto [entity, sprite, transform] : entities.each()) {
    bool need_to_render = in_camera_bound(map, transform.position, camera) &&
                          is_renderable(map, transform, sprite);

    if (need_to_render) {
      render_sprite(app->registry, entity, app->renderer, camera, transform,
                    sprite, map->tile_size);
    }
  }
}

bool in_camera_bound(const Map *map, const Position &position,
                     const Camera &camera) {
  return position.x >= camera.position.x - map->tile_size.w &&
         position.y >= camera.position.y - map->tile_size.h &&
         position.x <= camera.position.x + camera.size.w &&
         position.y <= camera.position.y + camera.size.h;
}

bool is_renderable(const Map *map, const Transform &transform,
                   const Sprite &sprite) {
  int depth = map->get_depth(sprite.depth, transform.position);

  return depth < Map::MAX_TILE_VISIBLE_ENTITIES;
}

void render_sprite(entt::registry &registry, entt::entity &entity,
                   SDL_Renderer *renderer, const Camera &camera,
                   const Transform &transform, const Sprite &sprite,
                   const Size &map_tile_size) {

#ifdef DEBUG_RENDER_SYSTEM
  printf("RenderSystem <- Camera(%i %i) (%i %i)\n", camera.position.x,
         camera.position.y, camera.size.w, camera.size.h);
  printf("RenderSystem <- Transform(%i %i) (%i %i)\n", transform.position.x,
         transform.position.y, transform.size.w, transform.size.h);
#endif

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

#ifdef DEBUG_RENDER_SYSTEM
  printf("RenderSystem <- SDL_Rect(%i %i) (%i %i)\n", target_rect.x,
         target_rect.y, target_rect.w, target_rect.h);
#endif

  if (sprite.textures.empty()) {
    const auto &color = sprite.color;

    SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, color.a);
    SDL_RenderFillRect(renderer, &target_rect);

    return;
  }

  auto [texture, tex_pos, tex_size] = sprite.textures.at(0);

  SDL_Rect texture_rect{
      tex_pos.x,
      tex_pos.y,
      tex_size.w,
      tex_size.h,
  };

  SDL_RenderCopy(renderer, texture, &texture_rect, &target_rect);

#ifdef DEBUG_COLLISION
  if (registry.has<RigidBody>(entity)) {
    const auto &rb = registry.get<RigidBody>(entity);
    SDL_Rect collision{
        .x = rb.position.x - camera.position.x,
        .y = rb.position.y - camera.position.y,
        .w = rb.size.w,
        .h = rb.size.h,
    };

    SDL_SetRenderDrawColor(renderer, 0, 255, 0, 255);
    SDL_RenderDrawRect(renderer, &collision);
  }
#endif
}
