#pragma once

#include <vector>

#include "circle.hpp"
#include "line.hpp"
#include "polygon.hpp"
#include "triangle.hpp"
#include "vector2.hpp"

namespace Engine {
    namespace Physics {
        bool collides(const Circle& a, const Circle& b);
        bool collides(const Line& line, const Line& b);
        bool collides(const Line& line, const Engine::Polygon& polygon);
        bool collides(const Line& line, const std::vector<Engine::Polygon>& obstacles);
        bool collides(const Engine::Vector2& point, const Engine::Triangle& triangle);

        Engine::Vector2 center(const Engine::Triangle& triangle);
    }
}
