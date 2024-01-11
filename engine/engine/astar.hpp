#pragma once

#include "navmesh.hpp"
#include "vector2.hpp"

namespace Engine {
    namespace IA {
        using Path = std::vector<Engine::Vector2>;

        namespace Navigation {
            int findTriangleForPoint(const Navmesh& navmesh, const Engine::Vector2& point);
            std::vector<int> path(Engine::IA::Navmesh& navmesh, int startTriangle, int goalTriangle);
            Path path(Engine::IA::Navmesh& navmesh, Engine::Vector2& start, Engine::Vector2& end);
        }
    }
}
