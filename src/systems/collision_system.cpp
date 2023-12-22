#include "systems.hpp"

namespace Systems {

    void CollisionSystem(entt::registry& registry) {
        auto collidable = registry.view<Components::Position, Components::CircleCollider>();

        collidable.each([&registry, &collidable](auto entityA, auto& positionA, auto& colliderA) {

            std::vector<entt::entity> collisions;
            collidable.each([&registry, &collisions, entityA, positionA, &colliderA](auto entityB, auto& positionB, auto& colliderB) {
                if (entityA == entityB) return;
                if (CheckCollisionCircles(positionA, colliderA.radius, positionB, colliderB.radius)) collisions.push_back(entityB);
            });

            if (collisions.size()) registry.emplace_or_replace<Components::Collision>(entityA, collisions);
            else registry.remove<Components::Collision>(entityA);
        });
    }

}
