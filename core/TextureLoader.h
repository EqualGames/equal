#ifndef EQUAL_TEXTURE_LOADER_H
#define EQUAL_TEXTURE_LOADER_H

#include "Types.h"
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <entt/entt.hpp>

struct Texture {
  Size size{0, 0};
  Ref<SDL_Texture> data{nullptr};

  Texture() = default;

  Texture(Size size, SDL_Texture *data) : size(size), data(data) {}
};

using TextureCache = entt::resource_cache<Texture>;

struct TextureLoader final : entt::resource_loader<TextureLoader, Texture> {
  Ref<Texture> load(SDL_Renderer *renderer, const std::string &path) const {

    SDL_Surface *image = IMG_Load(path.c_str());
    Size size{0, 0};
    SDL_Texture *texture = nullptr;

    if (image == nullptr) {
      printf("Unable to load image %s! SDL_image Error: %s\n", path.c_str(),
             IMG_GetError());
    } else {

      SDL_SetColorKey(image, SDL_TRUE,
                      SDL_MapRGB(image->format, 0, 0xFF, 0xFF));

      texture = SDL_CreateTextureFromSurface(renderer, image);

      if (texture == nullptr) {
        printf("Unable to create texture from %s! SDL Error: %s\n",
               path.c_str(), SDL_GetError());
      }

      if (SDL_QueryTexture(texture, nullptr, nullptr, &size.w, &size.h)) {
        printf("Unable to read texture information: %s! SDL Error: %s\n",
               path.c_str(), SDL_GetError());
      }

      SDL_FreeSurface(image);
      image = nullptr;
    }

    return make_ref<Texture>(size, texture);
  }
};

#endif // EQUAL_TEXTURE_LOADER_H
