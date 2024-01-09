#include <raylib.h>
#include "physics.hpp"

namespace Engine {
    namespace Physics {
        bool collides(Circle& a, Circle& b) {
            return CheckCollisionCircles(a.center, a.radius, b.center, b.radius);
        }
    }
}
