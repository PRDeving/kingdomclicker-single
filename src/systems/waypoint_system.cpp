#include <engine/engine.hpp>
#include "systems.hpp"

namespace Systems {

    void WaypointSystem(entt::registry& registry, Engine::Input::Input& input, Vector2& cursor) {
        std::vector<entt::entity> selected;
        registry.view<Components::Selectable, Components::MovementPath>().each([&selected](auto entity, auto& selectable, auto& movement_path) {
            if (selectable.selected) selected.push_back(entity);
        });

        if (
            selected.size()
            && (input.mouse.pressed & MOUSE_RIGHT)
        ) {
            auto view = registry.view<Components::MovementPath, Components::Position>();
            entt::entity leader = selected.front();
            auto& l_movement_path = view.get<Components::MovementPath>(leader);
            auto& l_position = view.get<Components::Position>(leader);

            if (l_movement_path.waypoints.size() && !(input.keyboard.down & KEY_SHIFT)) l_movement_path.waypoints.clear();
            l_movement_path.waypoints.push_back(cursor);
            Engine::Random::Rng rng((unsigned long int)leader);

            for (auto entity: selected) {
                auto& movement_path = view.get<Components::MovementPath>(entity);
                auto& position = view.get<Components::Position>(entity);

                movement_path.leader = leader;
                if (movement_path.leader == entity) continue;

                if (movement_path.waypoints.size() && !(input.keyboard.down & KEY_SHIFT)) movement_path.waypoints.clear();
                movement_path.waypoints.push_back(l_movement_path.waypoints.back() - Vector2{ Engine::Random::range(-50.0f, 50.0f), Engine::Random::range(-50.0f, 50.0f) });
            }
        }
    }

}
