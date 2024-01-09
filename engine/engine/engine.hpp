#pragma once
#include <raylib.h>
#include "render.hpp"
#include "input.hpp"
#include "random.hpp"
#include "physics.hpp"

typedef Vector2 Vector2;

namespace Engine {
    bool isRunning();
    void init(const char* title);
    void close();
    void loop(std::function<void(float)> frame, const float interval, bool* interrupt);
}

Vector2 operator-(const Vector2& a, const float b);
Vector2 operator/(const Vector2& a, const float b);
Vector2 operator*(const Vector2& a, const float b);

Vector2 operator+(const Vector2& a, const Vector2& b);
Vector2 operator-(const Vector2& a, const Vector2& b);
Vector2 operator/(const Vector2& a, const Vector2& b);
Vector2 operator*(const Vector2& a, const Vector2& b);
