#pragma once

#include <vector>
#include <string>
#include <unordered_map>
#include <entt/entt.hpp>
#include <engine/engine.hpp>

namespace Components {

    struct Camera {};

    struct Position : Engine::Vector2 { };
    struct Scale : Engine::Vector2 { };
    struct Direction : Engine::Vector2 { };
    typedef float Speed;

    // INTERACTION RELATED
    struct PlayerControled { };
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
