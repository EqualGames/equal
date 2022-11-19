#pragma once

#include "../export.h"
#include "Texture.h"
#include "Types.h"

namespace eq {

    class Application;
    class Map;
    class Entity;

    class EQ_EXPORT Scene {

    public:
        TextureManager textures{};
        Application *app{nullptr};
        Ref<Map> map{nullptr};

        virtual ~Scene() {
            registry.clear();
            textures.clear();
            map = nullptr;
            app = nullptr;
        }

        virtual void init() = 0;
        virtual void event(const Event &event) = 0;
        virtual void update(float delta_time) = 0;
        virtual void draw(Renderer *renderer) = 0;
        virtual Entity &get_camera() = 0;
        virtual Entity &get_player() = 0;

        Entity create_entity(const std::string &name = std::string());

    protected:
        friend class Entity;
        friend class Map;
        friend class Application;

        entt::registry registry;
        bool loading{true};
    };

}// namespace eq
