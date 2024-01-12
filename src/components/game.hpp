#pragma once

#include <vector>
#include <entt/entt.hpp>
#include <engine/engine.hpp>
#include "../types.hpp"

#include "../item.hpp"

namespace Components {

    using Equip = std::vector<Item>;

    typedef std::vector<Task> TaskQueue;

    struct TaskMoveTo : Engine::Vector2 { };

    struct TaskMoveToTarget {
        entt::entity target;
    };

    struct TaskCollectFromTarget {
        entt::entity target;
    };

}
