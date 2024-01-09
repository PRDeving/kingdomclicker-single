#include "collision.hpp"
#include <engine/engine.hpp>
#include "../components/components.hpp"

namespace Systems {

    void CollisionSystem(entt::registry& registry, float deltatime) {
        auto collidable = registry.view<Components::Position, Components::CircleCollider>();

        registry.view<Components::Position, Components::CircleCollider, Components::Direction, Components::Speed>().each(
                [&registry, &collidable, deltatime](auto entityA, auto& positionA, auto& colliderA, auto& directionA, auto& speedA) {

            auto a = Engine::Physics::Circle{positionA + directionA * speedA * deltatime, colliderA.radius};

            std::vector<entt::entity> collisions;
            collidable.each([&registry, deltatime, &collisions, entityA, &a, &colliderA](auto entityB, auto& positionB, auto& colliderB) {
                if (entityA == entityB || !(colliderA.collisionMask & colliderB.layer)) return;

                auto b = Engine::Physics::Circle{ positionB, colliderB.radius };
                if (Engine::Physics::collides(a, b)) collisions.push_back(entityB);
            });

            if (collisions.size()) registry.emplace_or_replace<Components::Collision>(entityA, collisions);
            else registry.remove<Components::Collision>(entityA);
        });
    }

}
