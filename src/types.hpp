#pragma once

enum ITEM {
    WOOD,
};

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
        Vector2 location;
        entt::entity target;
    };
};

typedef struct ItemStack {
    ITEM type;
    unsigned int amount;
} Item;
