#pragma once
#include "../types.hpp"

namespace Components {

    struct Unit { };

    struct Resource {
        ITEM type;
    };

    struct Inventory {
        std::vector<ItemStack> items;
    };

    struct Storage {
        unsigned int amount;
        unsigned int capacity;
    };

    typedef std::vector<Task> TaskQueue;
    struct TaskMoveTo : Vector2 { };
    struct TaskMoveToTarget {
        entt::entity target;
    };
    struct TaskCollectFromTarget {
        entt::entity target;
    };

}
