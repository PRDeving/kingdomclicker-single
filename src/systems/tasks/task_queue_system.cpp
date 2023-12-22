#include "../systems.hpp"

namespace Systems {

    void TaskQueueSystem(entt::registry& registry) {
        registry.view<Components::TaskQueue>(entt::exclude<Components::TaskMoveTo, Components::TaskFollow>).each([&registry](auto entity, auto& tasks) {
            if (tasks.empty()) return;

            Task task = tasks.front();
            switch(task.type) {
                case ACTION::MOVE:
                    registry.emplace_or_replace<Components::TaskMoveTo>(entity, task.location);
                break;
                case ACTION::FOLLOW:
                    registry.emplace_or_replace<Components::TaskFollow>(entity, task.target);
                break;
            }
            tasks.erase(tasks.begin());
        });
    }

}
