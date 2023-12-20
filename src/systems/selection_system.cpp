#include "systems.hpp"

namespace Systems {

    void SelectionSystem(entt::registry& registry, Engine::Input::Input& input, Camera2D& camera) {
        Vector2 cursor = GetScreenToWorld2D(input.mouse.cursor, camera);
        Vector2 p0 = GetScreenToWorld2D(Vector2{ input.mouse.rect.x, input.mouse.rect.y }, camera);

        registry.view<Components::Position, Components::Collider, Components::Selectable>().each([&input, &cursor, &p0, &camera](auto& position, auto& collider, auto& selectable) {
            float distance = sqrt(pow(position.x - cursor.x, 2) + pow(position.y - cursor.y, 2));
            bool isClick = input.mouse.pressed & MOUSE_LEFT;

            selectable.selected = (

                // basic select on click
                (isClick && distance <= collider.radius)

                // additive select on click
                || (isClick && (input.keyboard.down & KEY_SHIFT) && selectable.selected)
            
                // keep selection from iteration to iteration if no click-out is executed
                || (!isClick && !input.mouse.rect.width && selectable.selected)

                // Rect selection (from JS)
                || (
                    input.mouse.rect.width
                    && (position.x >= p0.x && position.x <= p0.x + input.mouse.rect.width)
                    && (position.y >= p0.y && position.y <= p0.y + input.mouse.rect.height)
                )

            );
        });
    }

}

