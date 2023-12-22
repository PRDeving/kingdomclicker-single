#include "systems.hpp"

namespace Systems {

    void CollisionSystem(entt::registry& registry, float deltatime) {
        auto collidable = registry.view<Components::Position, Components::CircleCollider>();

        registry.view<Components::Position, Components::CircleCollider, Components::Direction, Components::Speed>().each(
                [&registry, &collidable, deltatime](auto entityA, auto& positionA, auto& colliderA, auto& directionA, auto& speedA) {

            std::vector<entt::entity> collisions;
            collidable.each([&registry, deltatime, &collisions, entityA, positionA, &colliderA, &directionA, speedA](auto entityB, auto& positionB, auto& colliderB) {
                if (entityA == entityB || !(colliderA.collisionMask & colliderB.layer)) return;
                if (CheckCollisionCircles(positionA + directionA * speedA * deltatime, colliderA.radius, positionB, colliderB.radius)) collisions.push_back(entityB);
            });

            if (collisions.size()) registry.emplace_or_replace<Components::Collision>(entityA, collisions);
            else registry.remove<Components::Collision>(entityA);
        });
    }

}
