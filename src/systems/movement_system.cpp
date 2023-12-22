#include "systems.hpp"

namespace Systems {

    void MovementSystem(entt::registry& registry, float deltatime) {
        registry.view<Components::Position, Components::Direction, Components::Speed>(entt::exclude<Components::Collision>).each([&deltatime](auto& position, auto direction, auto speed) {
            position.x += direction.x * speed * deltatime;
            position.y += direction.y * speed * deltatime;
        });
    }

}

