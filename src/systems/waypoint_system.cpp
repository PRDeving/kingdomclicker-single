#include "systems.hpp"

namespace Systems {

    void WaypointSystem(entt::registry& registry, Engine::Input::Input& input, Vector2& cursor, float deltatime) {

        registry.view<Components::Selectable, Components::Position, Components::Velocity, Components::Rotation, Components::MovementPath>().each(
            [&input, &cursor, &deltatime](auto& selectable, auto& position, auto& velocity, auto& rotation, auto& movement_path) {
                if (
                    selectable.selected
                    && (input.mouse.pressed & MOUSE_RIGHT)
                    && (movement_path.path.size() && !(input.keyboard.down & KEY_SHIFT))
                ) movement_path.path.clear();

                if (
                    selectable.selected
                    && (input.mouse.pressed & MOUSE_RIGHT)
                    && (
                        movement_path.path.size() == 0
                        || (input.keyboard.down & KEY_SHIFT)
                    )
                ) movement_path.path.push_back(cursor);

                if (movement_path.path.empty()) return;

                auto next = movement_path.path.front();
                float distance = sqrt(pow(position.x - next.x, 2) + pow(position.y - next.y, 2));

                if (distance > velocity.speed * deltatime) {
                    rotation.radians = atan2(next.y - position.y, next.x - position.x);
                    velocity.dx = (next.x - position.x) / distance;
                    velocity.dy = (next.y - position.y) / distance;
                    velocity.speed = 0.1f;
                } else {
                    velocity.dx = 0.0f;
                    velocity.dy = 0.0f;
                    velocity.speed = 0.0f;
                    movement_path.path.erase(movement_path.path.begin());
                }
            }
        );
    }

}
