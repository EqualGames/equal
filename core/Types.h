#ifndef EQUAL_TYPES_H
#define EQUAL_TYPES_H

#include <cstdint>

enum Direction : uint8_t {
    None = 1 << 0,
    Up = 1 << 1,
    Down = 1 << 2,
    Left = 1 << 3,
    Right = 1 << 4,
};

struct Position {
    int x;
    int y;
};

struct Size {
    int w;
    int h;
};

struct Color {
    uint8_t r{0};
    uint8_t g{0};
    uint8_t b{0};
    uint8_t a{255};

    Color() = default;

    Color(uint8_t r, uint8_t g, uint8_t b) : r(r), g(g), b(b), a(255) {}

    Color(uint8_t r, uint8_t g, uint8_t b, uint8_t a) : r(r), g(g), b(b), a(a) {}
};

#endif //EQUAL_TYPES_H
