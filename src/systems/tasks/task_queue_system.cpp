#include "queue.hpp"
#include <entt/entt.hpp>
#include "../../components/components.hpp"

namespace Systems {

    void TaskQueueSystem(entt::registry& registry) {
        registry.view<Components::TaskQueue>(entt::exclude<
            Components::TaskMoveTo,
            Components::TaskMoveToTarget,
            Components::TaskCollectFromTarget
        >).each([&registry](auto entity, auto& tasks) {
            if (tasks.empty()) return;

            Task task = tasks.front();
            switch(task.type) {
                case ACTION::MOVE:
                    registry.emplace_or_replace<Components::TaskMoveTo>(entity, task.location);
                break;
                case ACTION::MOVE_TO_TARGET:
                    registry.emplace_or_replace<Components::TaskMoveToTarget>(entity, task.target);
                break;
                case ACTION::COLLECT:
                    registry.emplace_or_replace<Components::TaskCollectFromTarget>(entity, task.target);
                break;
            }
            tasks.erase(tasks.begin());
        });
    }

}
