#pragma once

enum ITEM {
    WOOD,
};

enum ACTION {
    MOVE,
    FOLLOW,
    COLLECT,
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
