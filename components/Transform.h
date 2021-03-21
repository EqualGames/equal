#ifndef EQUAL_TRANSFORM_H
#define EQUAL_TRANSFORM_H

#include "../core/Types.h"

struct Transform {
  Position position{0, 0, 0};
  Size size{0, 0};

  Transform() = default;

  Transform(Position position, Size size) : position(position), size(size){};

  Transform(int x, int y, int w, int h) {
    this->position.x = x;
    this->position.y = y;
    this->size.w = w;
    this->size.h = h;
  }

  Transform(int x, int y, int z, int w, int h) {
    this->position.x = x;
    this->position.y = y;
    this->position.z = z;
    this->size.w = w;
    this->size.h = h;
  }
};

#endif // EQUAL_TRANSFORM_H
