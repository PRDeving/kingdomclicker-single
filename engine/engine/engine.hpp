#pragma once
#include "input.hpp"
#include "random.hpp"
#include "assets.hpp"
#include "scene.hpp"

#include "texture.hpp"
#include "sprite.hpp"
#include "render.hpp"
#include "camera.hpp"
#include "physics.hpp"
#include "navmesh.hpp"

#include "color.hpp"
#include "vector2.hpp"
#include "rectangle.hpp"
#include "circle.hpp"
#include "polygon.hpp"

namespace Engine {
    bool isRunning();
    void init(const char* title);
    void close();
    void loop(std::function<void(float)> frame, const float interval, bool* interrupt);
}
