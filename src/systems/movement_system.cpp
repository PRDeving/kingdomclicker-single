#include "systems.hpp"

namespace Systems {

    void MovementSystem(entt::registry& registry, float deltatime) {
        registry.view<Components::Position, Components::Velocity>().each([&deltatime](auto& position, auto& velocity) {
            position.x += velocity.dx * velocity.speed * deltatime;
            position.y += velocity.dy * velocity.speed * deltatime;
        });
    }

}

