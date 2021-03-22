#ifndef EQUAL_TYPES_H
#define EQUAL_TYPES_H

#include <cstdint>
#include <memory>

template <typename T> using Scope = std::unique_ptr<T>;
template <typename T, typename... Args>
constexpr Scope<T> make_scope(Args &&...args) {
  return std::make_unique<T>(std::forward<Args>(args)...);
}

template <typename T> using Ref = std::shared_ptr<T>;
template <typename T, typename... Args>
constexpr Ref<T> make_ref(Args &&...args) {
  return std::make_shared<T>(std::forward<Args>(args)...);
}

struct DirectionalStatus {
  bool up{false};
  bool down{false};
  bool left{false};
  bool right{false};
};

enum Direction {
  None,
  Up,
  Down,
  Left,
  Right,
};

struct Position {
  int x{0};
  int y{0};
  int z{0};

  bool operator==(const Position &right) const {
    return this->x == right.x && this->y == right.y && this->z == right.z;
  }

  bool operator!=(const Position &right) const {
    return this->x != right.x || this->y != right.y || this->z != right.z;
  }
};

struct Size {
  int w{0};
  int h{0};

  Size operator/(int value) const {
    return Size{this->w / value, this->h / value};
  }
  Size operator*(int value) const {
    return Size{this->w * value, this->h * value};
  }
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

#endif // EQUAL_TYPES_H
