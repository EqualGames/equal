#include "Scene.h"
#include "../components/TagComponent.h"
#include "Entity.h"
#include "Map.h"

namespace eq {

    Entity Scene::create_entity(const std::string &name) {
        Entity entity{registry.create(), this};

        std::string generated_name{fmt::format("Entity_{}", (uint32_t) entity)};
        entity.add_component<TagComponent>(name.empty() ? generated_name : name);

        return entity;
    }

}// namespace eq
