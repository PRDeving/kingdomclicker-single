#pragma once

#include "navmesh.hpp"
#include "vector2.hpp"

namespace Engine {
    namespace IA {
        using Path = std::vector<Engine::Vector2>;

        namespace Navigation {
            Path path(Engine::IA::Navmesh& navmesh, Engine::Vector2& start, Engine::Vector2& end);
        }
    }
}
