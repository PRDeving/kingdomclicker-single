#pragma once
#include <engine/engine.hpp>
#include <vector>

namespace Components {

    struct Camera {};

    struct Scale : Engine::Vector2 { };

    // MOVEMENT RELATED
    struct Position : Engine::Vector2 { };
    struct Direction : Engine::Vector2 { };
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
    typedef std::vector<Engine::Vector2> Waypoints;
    typedef std::vector<Engine::Vector2> Pathfinding;

    // TASK RELATED
    struct Target {
        entt::entity entity;
        bool onRange;
    };

    // // RENDERING RELATED
    struct Sprite : Engine::Sprite {};

    struct Animation {
        std::unordered_map<std::string, std::vector<int>>* animations;
        std::string current;
        unsigned char frame;
        float frameTime;
        float elapsed;
    };

}
