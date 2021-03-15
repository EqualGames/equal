#include "RendererSystem.h"

void renderer_system(entt::registry &registry, SDL_Renderer *renderer,
                     const entt::entity &camera) {
  const auto cam = registry.get<Camera>(camera);
  const auto map = registry.view<Map>();

  for (auto [entity, map] : map.each())
    for (auto floor : map.floors)
      for (auto tile : floor->tiles)
        for (auto thing : tile->things) {

          if (thing->flags & TileFlag::ENTITY) {
            render_sprite(registry, renderer, cam, thing->id);
            continue;
          }

          auto tileset = map.get_tileset(thing->gid);

          if (!tileset) {
            continue;
          }

          SDL_Rect texture_rect = tileset->get_texture_position(thing->gid);
          SDL_Rect target_rect{
              (tile->position.x * map.tile_size.w) - cam.position.x,
              (tile->position.y * map.tile_size.h) - cam.position.y,
              texture_rect.w,
              texture_rect.h,
          };

          if (texture_rect.w > map.tile_size.w) {
            target_rect.x -=
                (texture_rect.w / map.tile_size.w) * (map.tile_size.w / 2);
          }

          if (texture_rect.h > map.tile_size.h) {
            target_rect.y -=
                (texture_rect.h / map.tile_size.h) * (map.tile_size.h / 2);
          }

#ifdef DEBUG
          if (thing->flags & TileFlag::COLLISION) {
            SDL_SetTextureColorMod(tileset->texture, 255, 0, 0);
          }
#endif
          SDL_RenderCopy(renderer, tileset->texture, &texture_rect,
                         &target_rect);

#ifdef DEBUG
          SDL_SetRenderDrawColor(renderer, 255, 0, 0, 0);
          SDL_RenderDrawRect(renderer, &target_rect);
#endif
        }
}

void render_sprite(entt::registry &registry, SDL_Renderer *renderer,
                   const Camera &camera, const entt::entity &entity) {
  const auto [transform, sprite] = registry.get<Transform, Sprite>(entity);

  const auto &position = transform.position;
  const auto &size = transform.size;

  SDL_Rect target_rect{
      (position.x * 32) - camera.position.x,
      (position.y * 32) - camera.position.y,
      size.w,
      size.h,
  };

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

  if (target_rect.w > 32) {
    target_rect.x -= (target_rect.w / 32) * (32 / 2);
  }

  if (target_rect.h > 32) {
    target_rect.y -= (target_rect.h / 32) * (32 / 2);
  }

  SDL_RenderCopy(renderer, texture, &texture_rect, &target_rect);
}
