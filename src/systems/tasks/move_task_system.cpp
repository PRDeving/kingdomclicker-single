#include "../systems.hpp"
#include <algorithm>

namespace Systems {

    void MoveTaskSystem(entt::registry& registry, float deltatime) {

        // CHECK COMPLETION MOVE TO TARGET
        registry.view<Components::TaskMoveToTarget, Components::Collision>().each([&registry, deltatime](auto entity, auto& task, auto& collisions) {
            if (std::find(collisions.begin(), collisions.end(), task.target) != collisions.end()) {
                registry.remove<Components::TaskMoveToTarget, Components::TaskMoveTo>(entity);
            }
        });

        // INIT MOVE TO TARGET
        auto units = registry.view<Components::Position>();
        registry.view<Components::TaskMoveToTarget>(entt::exclude<Components::TaskMoveTo>).each([&registry, &units](auto entity, auto& task) {
            auto location = units.get<Components::Position>(task.target);
            registry.emplace_or_replace<Components::TaskMoveTo>(entity, location);
        });




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
