#include "hover.hpp"
#include <entt/entt.hpp>
#include <engine/engine.hpp>
#include "../components/components.hpp"

namespace Systems {

    void HoverSystem(entt::registry& registry, Engine::Input::Input& input, Engine::Camera2D& camera) {
        Engine::Vector2 cursor = Engine::Camera::screenToWorld(input.mouse.cursor, camera);
        // Engine::Vector2 p0 = Engine::Camera::screenToWorld(Engine::Vector2{ input.mouse.rect.x, input.mouse.rect.y }, camera);

        Engine::Vector2 p0 = Engine::Camera::screenToWorld(input.mouse.rect.point, camera);

        auto view = registry.view<Components::Hovered>();
        registry.view<Components::Position, Components::CircleCollider>().each([&registry, &input, &cursor, &p0, &view, &camera](auto entity, auto& position, auto& collider) {
            float distance = sqrt(pow(position.x - cursor.x, 2) + pow(position.y - cursor.y, 2));
            bool isHovered = view.contains(entity);

            bool hover = (
                distance <= collider.radius
                || (
                    input.mouse.rect.size.x
                    && (position.x >= p0.x && position.x <= p0.x + input.mouse.rect.size.x)
                    && (position.y >= p0.y && position.y <= p0.y + input.mouse.rect.size.y)
                )

            );
            if (hover && !isHovered) registry.emplace<Components::Hovered>(entity);
            else if (!hover && isHovered) registry.remove<Components::Hovered>(entity);
        });
    }

}

