#ifdef RAYLIB
#include "../physics.hpp"

#include <raylib.h>
#include "../circle.hpp"

namespace Engine {
    namespace Physics {
        bool collides(Circle& a, Circle& b) {
            return CheckCollisionCircles(
                (::Vector2&)a.center, a.radius,
                (::Vector2&)b.center, b.radius
            );
        }
    }
}
#endif
