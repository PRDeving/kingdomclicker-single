#pragma once

#include "engine.hpp"

namespace Engine {
    namespace Physics {

        typedef struct Circle {
            Vector2 center;
            float radius;
        } Circle;

        bool collides(Circle& a, Circle& b);
    }
}
