#include "systems.hpp"
#include <algorithm>

namespace Systems {

    void CollectionSystem(entt::registry& registry) {
        registry.view<Components::Unit, Components::Target, Components::Collision>().each([&registry](auto entity, auto& target, auto& collisions) {
            target.onRange = (std::find(collisions.begin(), collisions.end(), target.entity) != collisions.end());
        });

        registry.view<Components::Target, Components::Waypoints>().each([&registry](auto entity, auto& target, auto& waypoints) {
            if (target.onRange) {
                waypoints.clear();
                registry.emplace_or_replace<Components::Collecting>(entity);
            }
        });

        registry.view<Components::Collecting>(entt::exclude<Components::Target>).each([&registry](auto entity) {
            registry.remove<Components::Collecting>(entity);
        });
    }

}
