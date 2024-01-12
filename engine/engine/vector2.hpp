#pragma once

namespace Engine {
    typedef struct Vector2 {
        float x;
        float y;
    } Vector2;

    Vector2 operator-(const Vector2& a, const float b);
    Vector2 operator*(const Vector2& a, const float b);
    Vector2 operator/(const Vector2& a, const float b);

    Vector2 operator+(const Vector2& a, const Vector2& b);
    Vector2 operator-(const Vector2& a, const Vector2& b);
    Vector2 operator*(const Vector2& a, const Vector2& b);
    Vector2 operator/(const Vector2& a, const Vector2& b);
    bool operator==(const Vector2& a, const Vector2& b);
    bool operator!=(const Vector2& a, const Vector2& b);
}
