#ifdef RAYLIB

#include "../camera.hpp"

#include <raylib.h>
#include "../vector2.hpp"

namespace Engine {
    namespace Camera {
        Engine::Vector2 screenToWorld(Engine::Vector2& point, Engine::Camera2D& camera) {
            auto p = GetScreenToWorld2D((::Vector2&)point, (::Camera2D&)camera);
            return Engine::Vector2{ p.x, p.y };
        }
    }
}

#endif
