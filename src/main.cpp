#include <iostream>
#include <entt/entt.hpp>
#include <cmath>
#include <raylib.h>

#include <engine/engine.hpp>
#include "components.hpp"
#include "systems/systems.hpp"
#include "assamblages/assamblages.hpp"

int main() {
    Engine::init("Kingdom Clicker");
    entt::registry registry;

    registry.ctx().emplace<Engine::Input::Input>();
    registry.ctx().emplace<Camera2D>(400.0f, 300.0f);

    entt::entity camera_entity = registry.create();
    registry.emplace<Components::Position>(camera_entity, 30.0f, 30.0f);
    registry.emplace<Components::Camera>(camera_entity);

    for(int i = 0; i < 8; i++) {
        Assamblages::Unit(registry, 15.0f * i, 10.0f);
    }

    auto &input = registry.ctx().get<Engine::Input::Input>();
    auto &camera = registry.ctx().get<Camera2D>();
    Engine::loop([&registry, &input, &camera](float deltatime) {
        Engine::Input::handle(&input);
        Systems::cameraUpdate(registry, camera, input, deltatime);
        Vector2 cursor = GetScreenToWorld2D(input.mouse.cursor, camera);

        Systems::SelectionSystem(registry, input, camera);
        Systems::WaypointSystem(registry, input, cursor, deltatime);
        Systems::MovementSystem(registry, deltatime);
        Systems::render(registry);

        if (input.mouse.rect.width) DrawRectangleLinesEx(input.mouse.rect, 2, ORANGE);

    }, (1000/60), NULL);

    Engine::close();
    return 0;
}
