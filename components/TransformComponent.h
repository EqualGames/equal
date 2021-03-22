#ifndef EQUAL_TRANSFORM_COMPONENT_H
#define EQUAL_TRANSFORM_COMPONENT_H

#include "../core/Types.h"

struct TransformComponent {
  Position position{0, 0, 0};
  Size size{0, 0};

  TransformComponent() = default;

  TransformComponent(Position position, Size size) : position(position), size(size){};

  TransformComponent(int x, int y, int w, int h) {
    this->position.x = x;
    this->position.y = y;
    this->size.w = w;
    this->size.h = h;
  }

  TransformComponent(int x, int y, int z, int w, int h) {
    this->position.x = x;
    this->position.y = y;
    this->position.z = z;
    this->size.w = w;
    this->size.h = h;
  }
};

#endif // EQUAL_TRANSFORM_COMPONENT_H
