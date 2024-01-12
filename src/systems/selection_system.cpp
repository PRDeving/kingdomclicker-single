#include "selection.hpp"
#include "../components/components.hpp"

namespace Systems {

    void SelectionSystem(entt::registry& registry, Engine::Input::Input& input) {
        bool action = (input.mouse.pressed & (char)Engine::Input::Button::LEFT || input.mouse.rect.size.x);
        if (!action) return;

        auto view = registry.view<Components::Selected>();
        auto hovered = registry.view<Components::Hovered>();

        registry.view<Components::PlayerControled>().each([&registry, &view, &hovered, &input, action](auto entity) {
            bool isSelected = view.contains(entity);
            bool isHovered = hovered.contains(entity);

            bool selected = (
                action
                && (isHovered || ((input.keyboard.down & (char)Engine::Input::Key::SHIFT) && isSelected))
            );

            if (selected) registry.emplace_or_replace<Components::Selected>(entity);
            else registry.remove<Components::Selected>(entity);
        });
    }

}

