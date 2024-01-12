#ifdef RAYLIB
#include "../physics.hpp"

#include <raylib.h>
#include "../circle.hpp"
#include "../vector2.hpp"

namespace Engine {
    namespace Physics {
        bool collides(const Circle& a, const Circle& b) {
            return CheckCollisionCircles(
                (::Vector2&)a.center, a.radius,
                (::Vector2&)b.center, b.radius
            );
        }

        bool collides(const Line& a, const Line& b) {
            return CheckCollisionLines(
               (::Vector2&)a.p0,
               (::Vector2&)a.p1,
               (::Vector2&)b.p0,
               (::Vector2&)b.p1,
                nullptr
            );
        }

        bool collides(const Engine::Vector2& point, const Triangle& triangle) {
            return CheckCollisionPointTriangle(
                (::Vector2&) point,
                (::Vector2&) triangle.p1,
                (::Vector2&) triangle.p2,
                (::Vector2&) triangle.p3
            );
        }
    }
}
#endif
