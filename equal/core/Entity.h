#pragma once

#include "../export.h"
#include "Scene.h"
#include <entt/entt.hpp>

namespace eq {

    class EQ_EXPORT Entity {
    public:
        Entity() = default;
        Entity(const Entity &entity) = default;
        Entity(entt::entity id, Scene *scene) : id(id), scene(scene) {}

        operator bool() const { return id != entt::null; }

        bool operator==(const Entity &other) const {
            return id == other.id && scene == other.scene;
        }

        bool operator!=(const Entity &other) const {
            return !(*this == other);
        }

        operator entt::entity() const { return id; }

        operator uint32_t() const { return (uint32_t) id; }

        template<typename Component>
        bool has_component() const {
            return scene->registry.all_of<Component>(id);
        }

        template<typename Component, typename... Args>
        Component &add_component(Args &&...args) {
            if (has_component<Component>()) {
                EQ_THROW("entity already has component!");
            }
            return scene->registry.emplace<Component>(id, std::forward<Args>(args)...);
        }

        template<typename Component>
        Component &get_component() {
            if (!has_component<Component>()) {
                EQ_THROW("entity does not have component!");
            }

            return scene->registry.get<Component>(id);
        }

        template<typename Component, typename... Args>
        void replace_component(Args &&...args) {
            scene->registry.emplace_or_replace<Component>(id, std::forward<Args>(args)...);
        }

        template<typename Component>
        void remove_component() {
            if (!has_component<Component>()) {
                EQ_THROW("entity does not have component!");
            }

            scene->registry.remove<Component>(id);
        }

        void destroy() { scene->registry.destroy(id); }

    private:
        entt::entity id{entt::null};
        Scene *scene{nullptr};
    };

}// namespace eq
