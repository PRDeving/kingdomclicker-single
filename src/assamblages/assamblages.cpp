#include "assamblages.hpp"

namespace Assamblages {
    entt::entity Unit(entt::registry& registry, float x, float y) {
        entt::entity e = registry.create();
        registry.emplace<Components::Position>(e, x, y);
        registry.emplace<Components::Velocity>(e, 0.0f);
        registry.emplace<Components::Rotation>(e);
        registry.emplace<Components::Collider>(e, 10.0f);
        registry.emplace<Components::Selectable>(e);
        return e;
    }
}
