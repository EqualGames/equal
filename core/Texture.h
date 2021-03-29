#ifndef EQUAL_TEXTURE_LOADER_H
#define EQUAL_TEXTURE_LOADER_H

#include "Exception.h"
#include "Helpers.h"
#include "Types.h"
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/Texture.hpp>
#include <entt/entt.hpp>
#include <filesystem>
#include <unordered_map>

using TextureResource = entt::resource_cache<sf::Texture>;

struct TextureResourceLoader final
    : entt::resource_loader<TextureResourceLoader, sf::Texture> {
  Ref<sf::Texture> load(const Ref<sf::RenderWindow> &renderer,
                        const std::string &path) const {

    auto texture = make_ref<sf::Texture>();
    texture->loadFromFile(path);

    return texture;
  }
};

struct TextureManager {
  using Texture = sf::Texture;

  std::unordered_map<std::string, Ref<Texture>> textures{};

  ~TextureManager() { textures.clear(); }

  inline void clear() { textures.clear(); }

  inline Ref<Texture> get(const std::string &id) {
    if (auto it = textures.find(id); it != textures.end()) {
      return it->second;
    }

    return nullptr;
  }

  inline void load(const Ref<sf::RenderWindow> &renderer,
                   const std::string &path) {

    auto id =
        split_pair(std::filesystem::path(path).filename().string(), '.').first;

    auto texture = make_ref<Texture>();

    if (!texture->loadFromFile(path)) {
      EQ_THROW(fmt::format("error on load texture({})", path));
    }

    textures.insert(std::make_pair(id, texture));
  }
};

#endif // EQUAL_TEXTURE_LOADER_H
