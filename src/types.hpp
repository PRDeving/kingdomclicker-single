#pragma once

#include <string>
#include <entt/entt.hpp>
#include <engine/engine.hpp>

enum ACTION {
    MOVE,
    MOVE_TO_TARGET,
    COLLECT,
};

enum LAYER {
    PLAYER =     0x01,
    RESOURCES =  0x02,
};

struct Task {
    ACTION type;
    union {
        Engine::Vector2 location;
        entt::entity target;
    };
};
