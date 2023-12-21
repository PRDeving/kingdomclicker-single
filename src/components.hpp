#pragma once
#include <raylib.h>
#include <vector>

struct Mouse {
    Vector2 cursor;
    char pressed;
    char down;
};

struct Input {
    Mouse mouse;
};

namespace Components {

    struct Camera {};

    struct Position : Vector2 { };

    struct Rotation {
        float radians;
    };

    struct Velocity {
        float dx;
        float dy;
        float speed;
    };

    struct Selectable {
        bool selected = false;
    };

    struct Collider {
        float radius;
    };

    struct MovementPath {
        std::vector<Vector2> waypoints;
        entt::entity leader;
    };

}
