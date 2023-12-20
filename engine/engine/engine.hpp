#pragma once
#include "render.hpp"
#include "input.hpp"

namespace Engine {
    bool isRunning();
    void init(const char* title);
    void close();
    void loop(std::function<void(float)> frame, const float interval, bool* interrupt);
}
