#include "../systems.hpp"

namespace Systems {

    void MoveTaskSystem(entt::registry& registry, float deltatime) {

        // CHECK COMPLETION
        registry.view<Components::TaskMoveTo, Components::Position, Components::Direction, Components::Speed>().each(
            [&registry, deltatime](auto entity, auto& task, auto& position, auto& direction, auto& speed) {
            float distance = sqrt(pow(position.x - task.x, 2) + pow(position.y - task.y, 2));
            if (distance <= speed * deltatime) registry.remove<Components::TaskMoveTo>(entity);
        });

        // INIT
        registry.view<Components::TaskMoveTo>(entt::exclude<Components::Waypoints>).each([&registry](auto entity, auto& target) {
            std::vector<Vector2> steps;
            steps.push_back(target);
            registry.emplace_or_replace<Components::Waypoints>(entity, steps);
        });

        // CLEAN
        registry.view<Components::Waypoints>(entt::exclude<Components::TaskMoveTo>).each([&registry](auto entity, auto& w) {
            registry.remove<Components::Waypoints>(entity);
        });
    }

}
