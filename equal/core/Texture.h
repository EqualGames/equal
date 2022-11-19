#pragma once

#include "Exception.h"
#include "Helpers.h"
#include "Types.h"
#include <filesystem>
#include <unordered_map>

namespace eq {

    class TextureManager {

    public:
        ~TextureManager() { textures.clear(); }

        void clear() { textures.clear(); }

        Texture *get(const std::string &id) {
            if (auto it = textures.find(id); it != textures.end()) {
                return it->second;
            }

            return nullptr;
        }

        void load(const Renderer *renderer, const std::string &path) {
            auto id =
                    split_pair(std::filesystem::path(path).filename().string(), '.').first;

            auto texture = new Texture();

            if (!texture->loadFromFile(path)) {
                EQ_THROW(fmt::format("error on load texture({})", path));
            }

            textures.insert(std::make_pair(id, texture));
        }

    private:
        std::unordered_map<std::string, Texture *> textures{};
    };

}// namespace eq
