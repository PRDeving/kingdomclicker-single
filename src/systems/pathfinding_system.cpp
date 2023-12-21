#include <engine/engine.hpp>
#include "systems.hpp"

namespace Systems {

    void PathfindingSystem(entt::registry& registry, float deltatime) {
        registry.view<Components::Position, Components::Velocity, Components::Rotation, Components::MovementPath>().each(
            [&registry, &deltatime](entt::entity entity, auto& position, auto& velocity, auto& rotation, auto& movement_path) {
                if (movement_path.waypoints.empty()) return;

                auto next = movement_path.waypoints.front();
                float distance = sqrt(pow(position.x - next.x, 2) + pow(position.y - next.y, 2));

                if (distance > velocity.speed * deltatime) {
                    rotation.radians = atan2(next.y - position.y, next.x - position.x);
                    velocity.dx = (next.x - position.x) / distance;
                    velocity.dy = (next.y - position.y) / distance;
                    velocity.speed = 0.1f;
                } else if (!movement_path.waypoints.size()) {
                    registry.remove<Components::MovementPath>(entity);
                } else {
                    velocity.speed = 0.0f;
                    movement_path.waypoints.erase(movement_path.waypoints.begin());
                }
        });
    }

}
