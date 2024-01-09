#pragma once
#include "input.hpp"
#include "random.hpp"

#include "render.hpp"
#include "camera.hpp"
#include "physics.hpp"

#include "color.hpp"
#include "vector2.hpp"
#include "rectangle.hpp"
#include "circle.hpp"

namespace Engine {
    bool isRunning();
    void init(const char* title);
    void close();
    void loop(std::function<void(float)> frame, const float interval, bool* interrupt);
}
