#include "vector2.hpp"

namespace Engine {
    Vector2 operator-(const Vector2& a, const float b) {
        return Vector2{a.x - b, a.y - b};
    }
    Vector2 operator*(const Vector2& a, const float b) {
        return Vector2{a.x * b, a.y * b};
    }
    Vector2 operator/(const Vector2& a, const float b) {
        return Vector2{a.x / b, a.y / b};
    }


    Vector2 operator+(const Vector2& a, const Vector2& b) {
        return Vector2{a.x + b.x, a.y + b.y};
    }
    Vector2 operator-(const Vector2& a, const Vector2& b) {
        return Vector2{a.x - b.x, a.y - b.y};
    }
    Vector2 operator*(const Vector2& a, const Vector2& b) {
        return Vector2{a.x * b.x, a.y * b.y};
    }
    Vector2 operator/(const Vector2& a, const Vector2& b) {
        return Vector2{a.x / b.x, a.y / b.y};
    }
}
