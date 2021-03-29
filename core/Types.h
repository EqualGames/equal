#ifndef EQUAL_TYPES_H
#define EQUAL_TYPES_H

#include <SFML/Graphics/Color.hpp>
#include <SFML/System/Vector2.hpp>
#include <SFML/Window/Event.hpp>
#include <cstdint>
#include <memory>

typedef sf::Event Event;
typedef sf::Keyboard Keyboard;

enum Direction : uint8_t {
  None = 0,
  Up = 1,
  Down = 2,
  Left = 3,
  Right = 4,
};

template <typename T> struct PositionType {
  T x{0};
  T y{0};
  T z{0};

  PositionType() = default;

  PositionType(uint32_t x, uint32_t y) : x(x), y(y), z(0) {}

  PositionType(int x, int y) : x(x), y(y), z(0) {}

  PositionType(double x, double y) : x(x), y(y), z(0) {}

  PositionType(float x, float y) : x(x), y(y), z(0) {}

  PositionType(uint32_t x, uint32_t y, uint32_t z) : x(x), y(y), z(z) {}

  PositionType(int x, int y, int z) : x(x), y(y), z(z) {}

  PositionType(double x, double y, double z) : x(x), y(y), z(z) {}

  PositionType(float x, float y, float z) : x(x), y(y), z(z) {}

  PositionType(const PositionType<uint32_t> &position)
      : x(position.x), y(position.y), z(position.z) {}

  PositionType(const PositionType<int> &position)
      : x(position.x), y(position.y), z(position.z) {}

  PositionType(const PositionType<double> &position)
      : x(position.x), y(position.y), z(position.z) {}

  PositionType(const PositionType<float> &position)
      : x(position.x), y(position.y), z(position.z) {}

  sf::Vector2<T> to_sfml() const { return sf::Vector2<T>(x, y); }

  bool operator==(const PositionType<T> &right) const {
    return x == right.x && y == right.y && z == right.z;
  }

  bool operator!=(const PositionType<T> &right) const {
    return x != right.x || y != right.y || z != right.z;
  }

  PositionType<T> operator/(T value) const {
    return PositionType<T>{x / value, y / value, z};
  }

  PositionType<T> operator*(T value) const {
    return PositionType<T>{x * value, y * value, z};
  }

  PositionType<T> operator+(T value) const {
    return PositionType<T>{x + value, y + value, z};
  }

  PositionType<T> operator-(T value) const {
    return PositionType<T>{x - value, y - value, z};
  }

  PositionType<T> operator+(const PositionType<T> &right) const {
    return PositionType<T>{x + right.x, y + right.y, z};
  }

  PositionType<T> operator-(const PositionType<T> &right) const {
    return PositionType<T>{x - right.x, y - right.y, z};
  }
};

using PositionU32 = PositionType<uint32_t>;
using Position = PositionType<int>;
using PositionDouble = PositionType<double>;
using PositionFloat = PositionType<float>;

template <typename T> struct SizeType {
  T w{0};
  T h{0};

  SizeType() = default;

  SizeType(uint32_t w, uint32_t h) : w(w), h(h) {}

  SizeType(int w, int h) : w(w), h(h) {}

  SizeType(double w, double h) : w(w), h(h) {}

  SizeType(float w, float h) : w(w), h(h) {}

  SizeType(const SizeType<uint32_t> &size) : w(size.w), h(size.h) {}

  SizeType(const SizeType<int> &size) : w(size.w), h(size.h) {}

  SizeType(const SizeType<double> &size) : w(size.w), h(size.h) {}

  SizeType(const SizeType<float> &size) : w(size.w), h(size.h) {}

  sf::Vector2<T> to_sfml() const { return sf::Vector2<T>(w, h); }

  SizeType<T> operator/(T value) const {
    return SizeType<T>{this->w / value, this->h / value};
  }

  SizeType<T> operator*(T value) const {
    return SizeType<T>{this->w * value, this->h * value};
  }

  SizeType<T> operator+(T value) const {
    return SizeType<T>{this->w + value, this->h + value};
  }

  SizeType<T> operator-(T value) const {
    return SizeType<T>{this->w - value, this->h - value};
  }

  SizeType<T> operator+(const SizeType<T> &right) const {
    return SizeType<T>{this->w + right.w, this->h + right.h};
  }

  SizeType<T> operator-(const SizeType<T> &right) const {
    return SizeType<T>{this->w - right.w, this->h - right.h};
  }
};

using Size = SizeType<uint32_t>;
using SizeI32 = SizeType<int>;
using SizeDouble = SizeType<double>;
using SizeFloat = SizeType<float>;

struct Color {
  uint8_t r{255};
  uint8_t g{255};
  uint8_t b{255};
  uint8_t a{255};

  Color() = default;

  Color(uint8_t r, uint8_t g, uint8_t b) : r(r), g(g), b(b), a(255) {}

  Color(uint8_t r, uint8_t g, uint8_t b, uint8_t a) : r(r), g(g), b(b), a(a) {}

  sf::Color to_sfml() const { return sf::Color(r, g, b, a); }
};

template <typename T1, typename T2> struct TransformType {
  PositionType<T1> position{0, 0, 0};
  SizeType<T2> size{0, 0};

  TransformType() = default;

  TransformType(const PositionType<T1> &position, const SizeType<T2> &size)
      : position(position), size(size){};

  TransformType(T1 x, T1 y, T2 w, T2 h) {
    this->position.x = x;
    this->position.y = y;
    this->size.w = w;
    this->size.h = h;
  }

  TransformType(T1 x, T1 y, T1 z, T2 w, T2 h) {
    this->position.x = x;
    this->position.y = y;
    this->position.z = z;
    this->size.w = w;
    this->size.h = h;
  }
};

using Transform = TransformType<int, uint32_t>;
using TransformInt = TransformType<int, int>;
using TransformDouble = TransformType<double, double>;
using TransformFloat = TransformType<float, float>;

template <typename T> struct RectType {
  T left{0};
  T top{0};
  T right{0};
  T bottom{0};

  RectType() = default;

  RectType(int left, int top, int right, int bottom)
      : left(left), top(top), right(right), bottom(bottom){};

  RectType(uint32_t left, uint32_t top, uint32_t right, uint32_t bottom)
      : left(left), top(top), right(right), bottom(bottom){};

  RectType(double left, double top, double right, double bottom)
      : left(left), top(top), right(right), bottom(bottom){};

  RectType(float left, float top, float right, float bottom)
      : left(left), top(top), right(right), bottom(bottom){};
};

using RectU32 = RectType<uint32_t>;
using Rect = RectType<int>;
using RectDouble = RectType<double>;
using RectFloat = RectType<float>;

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

#endif // EQUAL_TYPES_H
