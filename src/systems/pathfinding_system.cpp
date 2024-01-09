#include "pathfinding.hpp"
#include <entt/entt.hpp>
#include <engine/engine.hpp>
#include "../components/components.hpp"

namespace Systems {

    void PathfindingSystem(entt::registry& registry, float deltatime) {
        registry.view<Components::Direction>(entt::exclude<Components::Waypoints>).each( [&registry](entt::entity entity, auto& direction) {
            registry.remove<Components::Direction>(entity);
        });

        registry.view<Components::Position, Components::Speed, Components::Waypoints>().each(
            [&registry, &deltatime](entt::entity entity, auto& position, auto speed, auto& waypoints) {
                if (!waypoints.empty()) {
                    auto next = waypoints.front();
                    float distance = sqrt(pow(position.x - next.x, 2) + pow(position.y - next.y, 2));

                    if (distance > speed * deltatime) {
                        registry.emplace_or_replace<Components::Direction>(entity,
                            (next.x - position.x) / distance,
                            (next.y - position.y) / distance
                        );
                    } else {
                        waypoints.erase(waypoints.begin());
                    }
                }

                if (waypoints.empty()) registry.remove<Components::Waypoints>(entity);
        });
    }

}
