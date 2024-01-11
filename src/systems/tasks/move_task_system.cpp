#include "./move.hpp"
#include <algorithm>
#include <entt/entt.hpp>
#include "../../components/components.hpp"

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
        registry.view<Components::Position, Components::TaskMoveTo>(entt::exclude<Components::Waypoints>).each([&registry](auto entity, auto& position, auto& target) {
            auto& navmesh = registry.ctx().get<Engine::IA::Navmesh>();
            std::vector<Engine::Vector2> steps = Engine::IA::Navigation::path(navmesh, position, target);
            if (!steps.size()) return;
            registry.emplace<Components::Waypoints>(entity, steps);
        });

        // CLEAN
        registry.view<Components::Waypoints>(entt::exclude<Components::TaskMoveTo>).each([&registry](auto entity, auto& w) {
            registry.remove<Components::Waypoints>(entity);
        });
    }

}
