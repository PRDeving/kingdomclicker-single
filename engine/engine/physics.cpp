#include "physics.hpp"
#include <vector>

#include "line.hpp"
#include "polygon.hpp"

namespace Engine {
    namespace Physics {
        bool collides(const Line& line, const Engine::Polygon& polygon) {
            for (int i = 1; i < polygon.size(); ++i) {
                auto side = Engine::Line{polygon[i-1], polygon[i]};
                if (Engine::Physics::collides(line, side)) return true;
            }
            return false;
        }

        bool collides(const Engine::Line& line, const std::vector<Engine::Polygon>& obstacles) {
            for (Engine::Polygon polygon : obstacles) {
                if (Engine::Physics::collides(line, polygon)) return true;
            }

            return false;
        }

        Engine::Vector2 center(const Triangle& triangle) {
            return {
                (triangle.p1.x + triangle.p2.x + triangle.p3.x) / 3.0f,
                (triangle.p1.y + triangle.p2.y + triangle.p3.y) / 3.0f
            };
        }
    }
}
