#include "systems.hpp"

namespace Systems {

    void SelectionSystem(entt::registry& registry, Engine::Input::Input& input, Vector2& cursor) {
        registry.view<Components::Position, Components::Collider, Components::Selectable>().each([&input, &cursor](auto& position, auto& collider, auto& selectable) {
            float distance = sqrt(pow(position.x - cursor.x, 2) + pow(position.y - cursor.y, 2));
            selectable.selected = ((input.mouse.pressed & MOUSE_LEFT) && (distance <= collider.radius))
            || (!(input.mouse.pressed & MOUSE_LEFT) && selectable.selected);
        });
    }

}

