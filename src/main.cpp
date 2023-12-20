#include <iostream>
#include <entt/entt.hpp>
#include <raylib.h>

#include <engine/engine.hpp>
#include "components.hpp"
#include "systems/systems.hpp"

int main() {
    Engine::init("Kingdom Clicker");
    entt::registry registry;
    registry.ctx().emplace<Input>();

    entt::entity camera = registry.create();
    registry.emplace<Components::Position>(camera, 30.0f, 30.0f);
    registry.emplace<Components::Camera>(camera, 400.0f, 300.0f);

    entt::entity e = registry.create();
    registry.emplace<Components::Position>(e, 10.0f, 10.0f);
    registry.emplace<Components::Collider>(e, 10.0f);
    registry.emplace<Components::Sprite>(e);

    Engine::loop([&registry](float deltatime) {

        Engine::Render::draw([&registry]() {
            ClearBackground(RAYWHITE);

            // auto& i = registry.ctx<Input>();
            auto& input = registry.ctx().get<Input>();
            input.mouse = GetMousePosition();

            Systems::cameraUpdate(registry);

            registry.view<Components::Sprite, Components::Position>().each([](auto& position) {
                DrawRectangle(position.x - 5, position.y - 5, 10, 10, LIGHTGRAY);
            });

            Systems::render(registry);
        });

    }, (1000/60), NULL);

    Engine::close();
    return 0;
}
