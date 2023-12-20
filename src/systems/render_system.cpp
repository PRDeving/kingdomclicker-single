#include <raylib.h>
#include "systems.hpp"
#include "../components.hpp"

namespace Systems {

    void render(entt::registry &registry){
        auto& input = registry.ctx().get<Input>();
        DrawRectangle(input.mouse.x - 5, input.mouse.y - 5, 10, 10, LIGHTGRAY);

        registry.view<Components::Camera>().each([&registry, input](auto& camera) {
            BeginMode2D(camera);

            registry.view<Components::Sprite, Components::Position>().each([](auto& position) {
                DrawRectangle(position.x - 5, position.y - 5, 10, 10, LIGHTGRAY);
            });

            EndMode2D();
            return;
        });
    }

}
