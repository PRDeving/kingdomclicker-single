#pragma once
#include <raylib.h>

struct Input {
    Vector2 mouse;
};

namespace Components {

    struct Camera : Camera2D {};

    struct Position {
        float x;
        float y;
    };

    struct Collider {
        float radius;
    };

    struct Sprite {
    };

}
