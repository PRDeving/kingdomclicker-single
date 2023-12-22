#include "systems.hpp"

namespace Systems {

    void SelectionSystem(entt::registry& registry, Engine::Input::Input& input) {
        bool action = (input.mouse.pressed & MOUSE_LEFT || input.mouse.rect.width);
        if (!action) return;

        auto view = registry.view<Components::Selected>();
        auto hovered = registry.view<Components::Hovered>();

        registry.view<Components::Unit>().each([&registry, &view, &hovered, &input, action](auto entity) {
            bool isSelected = view.contains(entity);
            bool isHovered = hovered.contains(entity);

            bool selected = (
                action
                && (isHovered || ((input.keyboard.down & KEY_SHIFT) && isSelected))
            );

            if (selected) registry.emplace_or_replace<Components::Selected>(entity);
            else registry.remove<Components::Selected>(entity);
        });
    }

}

