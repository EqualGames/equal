#ifndef EQUAL_CAMERA_SYSTEM_H
#define EQUAL_CAMERA_SYSTEM_H

#include "../components/CameraComponent.h"
#include "../components/TransformComponent.h"
#include "../core/Scene.h"
#include "../core/Types.h"
#include <entt/entity/registry.hpp>

namespace Tiled::Camera {

void system(Scene *scene);

} // namespace Tiled::Camera

#endif // EQUAL_CAMERA_SYSTEM_H
