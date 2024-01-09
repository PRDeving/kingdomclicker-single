#pragma once
#include <engine/engine.hpp>
#include <vector>

namespace Components {

    struct Camera {};

    // MOVEMENT RELATED
    struct Position : Vector2 { };
    struct Direction : Vector2 { };
    typedef float Speed;

    // INTERACTION RELATED
    struct Hovered { };
    struct Selected { };

    // COLLISION RELATED
    struct CircleCollider {
        float radius;
        char layer;
        char collisionMask;
    };
    typedef std::vector<entt::entity> Collision;

    // PATHFINDING RELATED
    typedef std::vector<Vector2> Waypoints;
    typedef std::vector<Vector2> Pathfinding;

    // TASK RELATED
    struct Target {
        entt::entity entity;
        bool onRange;
    };

}
