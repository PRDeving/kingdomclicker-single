#include <iostream>
#include <entt/entt.hpp>
#include <cmath>
#include <chrono>
#include <raylib.h>
#include <random>

#include <engine/engine.hpp>
#include "components/components.hpp"
#include "systems/systems.hpp"
#include "assamblages/assamblages.hpp"

/*
 * TODO
 *
 * - Crash if rclick + shift mixing units from 2 different groups
 *   reproduce:
 *      - group A, set move tasks queue with shift
 *      - group B, set move tasks queue with shift
 *      - selection with some from A and B, set queue with shift
 *      crash
 *  probably a leader set error (contains assertion failed)
 *
 */

unsigned long int seed = 0;

void fixedUpdate(entt::registry& registry, float deltatime) {
    Systems::PathfindingSystem(registry, deltatime);
    Systems::MovementSystem(registry, deltatime);
    Systems::CollisionSystem(registry);
}

int main() {
    Engine::init("Kingdom Clicker");

    entt::registry registry;
    registry.ctx().emplace<Engine::Input::Input>();
    registry.ctx().emplace<Camera2D>(400.0f, 300.0f);

    entt::entity camera_entity = registry.create();
    registry.emplace<Components::Position>(camera_entity, 30.0f, 30.0f);
    registry.emplace<Components::Camera>(camera_entity);

    entt::entity tree = registry.create();
    registry.emplace<Components::Position>(tree, 100.0f, 100.0f);
    registry.emplace<Components::CircleCollider>(tree, 13.0f);
    registry.emplace<Components::Resource>(tree, ITEM::WOOD);
    registry.emplace<Components::Storage>(tree, 100u, 100u);

    for(int i = 0; i < 8; i++) {
        Assamblages::Unit(registry, 15.0f * i, 10.0f);
    }

    auto &input = registry.ctx().get<Engine::Input::Input>();
    auto &camera = registry.ctx().get<Camera2D>();

    Engine::loop([&registry, &input, &camera](float deltatime) {
        Engine::Input::handle(&input);
        Systems::cameraUpdate(registry, camera, input, deltatime);
        Vector2 cursor = GetScreenToWorld2D(input.mouse.cursor, camera);

        Systems::HoverSystem(registry, input, camera);
        Systems::SelectionSystem(registry, input);
        Systems::TaskQueueSystem(registry);
        
        if (input.mouse.pressed & MOUSE_RIGHT) {
            auto entities = registry.view<Components::Selected, Components::TaskQueue>();
             entt::entity leader = *entities.begin();

             for (auto entity : entities) {
                 auto& tasks = registry.get<Components::TaskQueue>(entity);
                 if (!input.keyboard.down & KEY_SHIFT) {
                     tasks.clear();
                     registry.remove<Components::TaskMoveTo>(entity);
                     registry.remove<Components::TaskFollow>(entity);
                 }

                 if (entity == leader) tasks.push_back(Task{ ACTION::MOVE, cursor });
                 else tasks.push_back(Task{ ACTION::FOLLOW, target: leader });
             }
        }

        Systems::MoveTaskSystem(registry, deltatime);
        Systems::FollowTaskSystem(registry);

        fixedUpdate(registry, 16.0f);

        Systems::render(registry);
        if (input.mouse.rect.width) DrawRectangleLinesEx(input.mouse.rect, 2, ORANGE);

    }, (1000/60), NULL);

    Engine::close();
    return 0;
}
