#include <sstream>
#include <iostream>
#include <raylib.h>
#include <engine/engine.hpp>
#include "systems.hpp"
#include "../components.hpp"

namespace Systems {

    void render(entt::registry &registry){
        Engine::Render::draw([&registry]() {
            auto& input = registry.ctx().get<Engine::Input::Input>();
            auto &camera = registry.ctx().get<Camera2D>();

            ClearBackground(RAYWHITE);

            std::ostringstream mouse_coords;
            mouse_coords << std::to_string(input.mouse.cursor.x).c_str() << "/" << std::to_string(input.mouse.cursor.y).c_str();
            DrawText(mouse_coords.str().c_str(), input.mouse.cursor.x - 10, input.mouse.cursor.y - 10, 10, BLACK);

            std::ostringstream camera_coords;
            camera_coords << std::to_string(camera.target.x).c_str() << "/" << std::to_string(camera.target.y).c_str();
            DrawText(camera_coords.str().c_str(), 10, 10, 10, BLACK);

            BeginMode2D(camera);

            registry.view<Components::Selectable, Components::Position>().each([](auto& selectable, auto& position) {
                DrawRectangle(position.x - 5, position.y - 5, 10, 10, selectable.selected ? RED : LIGHTGRAY);
            });

            EndMode2D();
        });
    }

}
