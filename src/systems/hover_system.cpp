#include "systems.hpp"

namespace Systems {

    void HoverSystem(entt::registry& registry, Engine::Input::Input& input, Camera2D& camera) {
        Vector2 cursor = GetScreenToWorld2D(input.mouse.cursor, camera);
        Vector2 p0 = GetScreenToWorld2D(Vector2{ input.mouse.rect.x, input.mouse.rect.y }, camera);

        auto view = registry.view<Components::Hovered>();
        registry.view<Components::Position, Components::CircleCollider>().each([&registry, &input, &cursor, &p0, &view, &camera](auto entity, auto& position, auto& collider) {
            float distance = sqrt(pow(position.x - cursor.x, 2) + pow(position.y - cursor.y, 2));
            bool isHovered = view.contains(entity);

            bool hover = (
                distance <= collider.radius
                || (
                    input.mouse.rect.width
                    && (position.x >= p0.x && position.x <= p0.x + input.mouse.rect.width)
                    && (position.y >= p0.y && position.y <= p0.y + input.mouse.rect.height)
                )

            );
            if (hover && !isHovered) registry.emplace<Components::Hovered>(entity);
            else if (!hover && isHovered) registry.remove<Components::Hovered>(entity);
        });
    }

}

