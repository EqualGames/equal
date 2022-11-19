#pragma once

#include "../components/SpriteComponent.h"
#include "../core/Scene.h"
#include "../core/Types.h"
#include "../export.h"

namespace eq::RendererSystem {

    EQ_EXPORT void run(Scene *scene, Registry &registry,
                       Renderer *renderer);

    /**
     * Check the position is into camera bounds
     */
    bool in_field_of_view(const Position &position, const Rect &camera_bounds);

    void draw(Renderer *renderer, const TransformFloat &transform,
              const SpriteComponent &sprite, Texture *texture);

}// namespace eq::RendererSystem
