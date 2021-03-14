#include "RendererSystem.h"

SDL_Texture *load_texture(SDL_Renderer *renderer, const std::string &path) {
    SDL_Texture *texture = nullptr;

    SDL_Surface *image = IMG_Load(path.c_str());

    if (image == nullptr) {
        printf("Unable to load image %s! SDL_image Error: %s\n", path.c_str(), IMG_GetError());
    } else {
        texture = SDL_CreateTextureFromSurface(renderer, image);

        if (texture == nullptr) {
            printf("Unable to create texture from %s! SDL Error: %s\n", path.c_str(), SDL_GetError());
        }

        SDL_FreeSurface(image);
        image = nullptr;
    }

    return texture;
}


void renderer_system(entt::registry &registry, SDL_Renderer *renderer, entt::entity &camera) {
    auto cam = registry.get<Camera>(camera);
    const auto &objects = registry.view<const Transform, const Sprite>();
    const auto &map = registry.view<const Map>();

    for (auto[entity, map]: map.each()) {
        for (auto floor : map.floors) {
            for (auto layer : floor->layers) {
                for (auto tile: layer->tiles) {

                    if (tile->texture_id == 0) continue;

                    auto texture_it = std::find_if(
                            map.textures.rbegin(),
                            map.textures.rend(),
                            [&](const std::pair<uint32_t, SDL_Texture *> &p) {
                                if (p.first <= tile->texture_id) {
                                    return true;
                                }

                                return false;
                            });

                    auto&[guid, texture_source] = *texture_it;

                    Size spritesheet{};
                    SDL_QueryTexture(texture_source, nullptr, nullptr, &spritesheet.w, &spritesheet.h);

                    int texture_id = (int) (tile->texture_id - guid);
                    auto tex_pos = Position{
                            map.tile_size.w * (texture_id % (spritesheet.w / map.tile_size.w)),
                            map.tile_size.h *
                            ((texture_id / (spritesheet.w / map.tile_size.w)) % (spritesheet.h / map.tile_size.h))
                    };

                    auto texture_rect = SDL_Rect{
                            tex_pos.x,
                            tex_pos.y,
                            map.tile_size.w,
                            map.tile_size.h,
                    };

                    auto target_rect = SDL_Rect{
                            tile->position.x - cam.position.x,
                            tile->position.y - cam.position.y,
                            map.tile_size.w,
                            map.tile_size.h,
                    };

                    SDL_RenderCopy(renderer, texture_source, &texture_rect, &target_rect);
                }
            }
        }

    }

    for (auto[entity, transform, sprite]: objects.each()) {
        auto &pos = transform.position;
        auto &size = transform.size;

        if (sprite.textures.empty()) {
            auto object_rect = new SDL_Rect{
                    pos.x - cam.position.x,
                    pos.y - cam.position.y,
                    size.w,
                    size.h,
            };

            auto color = sprite.color;
            SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, color.a);
            SDL_RenderFillRect(renderer, object_rect);

            continue;
        }

        auto[texture, tex_pos, tex_size] = sprite.textures.at(0);

        auto texture_rect = SDL_Rect{
                tex_pos.x,
                tex_pos.y,
                tex_size.w,
                tex_size.h,
        };

        auto target_rect = SDL_Rect{
                pos.x - cam.position.x,
                pos.y - cam.position.y,
                size.w,
                size.h,
        };

        SDL_RenderCopy(renderer, texture, &texture_rect, &target_rect);
    }
}
