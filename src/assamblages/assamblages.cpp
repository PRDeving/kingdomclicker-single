#include "assamblages.hpp"

namespace Assamblages {
    entt::entity Unit(entt::registry& registry, float x, float y) {
        entt::entity e = registry.create();
        registry.emplace<Components::Unit>(e);
        registry.emplace<Components::Position>(e, x, y);
        registry.emplace<Components::Speed>(e, 0.1f);
        registry.emplace<Components::CircleCollider>(e, 5.0f, LAYER::PLAYER, LAYER::RESOURCES);
        registry.emplace<Components::Storage>(e, 0u, 10u);
        registry.emplace<Components::TaskQueue>(e);
        return e;
    }
}
