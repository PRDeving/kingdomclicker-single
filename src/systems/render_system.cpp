#include <sstream>
#include <iostream>
#include "systems.hpp"

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

            auto selected = registry.view<Components::Selected>();
            auto collecting = registry.view<Components::Collecting>();
            registry.view<Components::Unit, Components::Position>().each([&selected, &collecting](auto entity, auto& position) {
                DrawRectangle(position.x - 5, position.y - 5, 10, 10, selected.contains(entity) ? RED : LIGHTGRAY);
                if (collecting.contains(entity)) DrawText("collecting", position.x - 20, position.y - 20, 10, BLACK);
            });

            registry.view<Components::Resource, Components::Storage, Components::Position>().each([](auto& resource, auto& storage, auto& position) {
                std::ostringstream txt;
                txt << std::to_string(storage.amount).c_str() << "/" << std::to_string(storage.capacity).c_str();
                DrawText(txt.str().c_str(), position.x - 20, position.y - 20, 10, BLACK);
                DrawRectangle(position.x - 5, position.y - 5, 10, 10, GREEN);
            });

            EndMode2D();
        });
    }

}
