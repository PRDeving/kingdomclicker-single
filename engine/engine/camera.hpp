#pragma once
#include "vector2.hpp"

namespace Engine {
    typedef struct Camera2D {
        Vector2 offset;
        Vector2 target;
        float rotation;
        float zoom;
    } Camera2D;

    namespace Camera {
        Vector2 screenToWorld(Vector2& point, Camera2D& camera);
    }
}
