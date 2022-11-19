#pragma once

#include "../export.h"
#include <SFML/Graphics/Color.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/Texture.hpp>
#include <SFML/System/Vector2.hpp>
#include <SFML/Window/Event.hpp>
#include <cstdint>
#include <entt/entt.hpp>
#include <memory>

namespace eq {

    using Event = sf::Event;
    using Keyboard = sf::Keyboard;
    using Registry = entt::registry;
    using Window = sf::RenderWindow;
    using Texture = sf::Texture;
    using Renderer = sf::RenderWindow;

    enum Direction {
        None = 0,
        Up = 1,
        Down = 2,
        Left = 3,
        Right = 4,
    };

    template<typename T>
    class EQ_EXPORT PositionType {
    public:
        T x{0};
        T y{0};
        T z{0};

        PositionType() = default;

        PositionType(const PositionType<T> &position) = default;

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

    template<typename T>
    class EQ_EXPORT SizeType {
    public:
        T w{0};
        T h{0};

        SizeType() = default;

        SizeType(const SizeType<T> &size) = default;

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

    class EQ_EXPORT Color {
    public:
        uint8_t r{255};
        uint8_t g{255};
        uint8_t b{255};
        uint8_t a{255};

        Color() = default;

        Color(const Color &color) = default;

        Color(uint8_t r, uint8_t g, uint8_t b, uint8_t a = 255)
            : r(r), g(g), b(b), a(a) {}

        sf::Color to_sfml() const { return sf::Color(r, g, b, a); }
    };

    template<typename T1, typename T2>
    class EQ_EXPORT TransformType {
    public:
        PositionType<T1> position{0, 0, 0};
        SizeType<T2> size{0, 0};

        TransformType() = default;

        TransformType(const TransformType<T1, T2> &transform) = default;

        TransformType(const PositionType<T1> &position, const SizeType<T2> &size) : position(position), size(size) {}

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

    template<typename T>
    class EQ_EXPORT RectType {
    public:
        T left{0};
        T top{0};
        T right{0};
        T bottom{0};

        RectType() = default;

        RectType(const RectType<T> &rect) = default;
    };

    using RectU32 = RectType<uint32_t>;
    using Rect = RectType<int>;
    using RectDouble = RectType<double>;
    using RectFloat = RectType<float>;

    template<typename T>
    using Scope = std::unique_ptr<T>;
    template<typename T, typename... Args>
    constexpr Scope<T> make_scope(Args &&...args) {
        return std::make_unique<T>(std::forward<Args>(args)...);
    }

    template<typename T>
    using Ref = std::shared_ptr<T>;
    template<typename T, typename... Args>
    constexpr Ref<T> make_ref(Args &&...args) {
        return std::make_shared<T>(std::forward<Args>(args)...);
    }

}// namespace eq
