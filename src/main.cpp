#include <iostream>
#include <entt/entt.hpp>
#include <cmath>
#include <chrono>
#include <random>

#include <engine/engine.hpp>
#include "components/components.hpp"
#include "assamblages/assamblages.hpp"

#include "systems/render.hpp"
#include "systems/camera_update.hpp"
#include "systems/hover.hpp"
#include "systems/selection.hpp"
#include "systems/pathfinding.hpp"
#include "systems/movement.hpp"
#include "systems/collision.hpp"

#include "systems/tasks/queue.hpp"
#include "systems/tasks/move.hpp"

/*
 * TODO
 *
 * (SOLVED?)
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
    Systems::CollisionSystem(registry, deltatime);
    Systems::MovementSystem(registry, deltatime);
}

int main() {
    Engine::init("Raid");

    Engine::Texture playerTexture = Engine::Assets::Texture::load("../assets/base.png");
    Engine::Sprite playerSprite(playerTexture, Engine::Vector2{ 4.0f, 4.0f });

    std::unordered_map<std::string, std::vector<int>> animations;
    animations["idle"] = std::vector<int>{0};
    animations["walk_down"] = std::vector<int>{0,1,2,3};
    animations["walk_up"] = std::vector<int>{4,5,6,7};
    animations["walk_right"] = std::vector<int>{8,9,10,11};
    animations["walk_left"] = std::vector<int>{12,13,14,15};


    entt::registry registry;
    registry.ctx().emplace<Engine::Input::Input>();
    registry.ctx().emplace<Engine::Camera2D>(400.0f, 300.0f);

    entt::entity camera_entity = registry.create();
    registry.emplace<Components::Position>(camera_entity, 30.0f, 30.0f);
    registry.emplace<Components::Camera>(camera_entity);

    entt::entity tree = registry.create();
    registry.emplace<Components::Position>(tree, 100.0f, 100.0f);
    registry.emplace<Components::CircleCollider>(tree, 6.0f, LAYER::RESOURCES);
    registry.emplace<Components::Resource>(tree, ITEM::WOOD);
    registry.emplace<Components::Storage>(tree, 100u, 100u);

    for(int i = 0; i < 8; i++) {
        auto unit = Assamblages::Unit(registry, 15.0f * i, 10.0f);
        registry.emplace<Components::Sprite>(unit, playerSprite);
        registry.emplace<Components::Animation>(unit, &animations, "idle", (unsigned char)0, 200.0f);
    }

    auto &input = registry.ctx().get<Engine::Input::Input>();
    auto &camera = registry.ctx().get<Engine::Camera2D>();

    int f = 0;
    float d = 0;

    Engine::loop([&registry, &input, &camera, &playerTexture, &playerSprite, &f, &d](float deltatime) {
        Engine::Input::handle(&input);
        Systems::cameraUpdate(registry, camera, input, deltatime);
        Engine::Vector2 cursor = Engine::Camera::screenToWorld(input.mouse.cursor, camera);

        Systems::HoverSystem(registry, input, camera);
        Systems::SelectionSystem(registry, input);

        fixedUpdate(registry, 16.0f);
        
        if (input.mouse.pressed & (char)Engine::Input::Button::RIGHT) {
            auto resourceHovered = registry.view<Components::Hovered, Components::Resource>();
            bool clicksResource = (resourceHovered.begin() != resourceHovered.end());

            auto entities = registry.view<Components::Selected, Components::TaskQueue>();
            entt::entity leader = *entities.begin();
            entt::entity resource = *resourceHovered.begin();

            for (auto entity : entities) {
                auto& tasks = registry.get<Components::TaskQueue>(entity);
                if (!input.keyboard.down & (char)Engine::Input::Key::SHIFT) {
                    tasks.clear();
                    registry.remove<
                        Components::TaskMoveTo,
                        Components::TaskMoveToTarget,
                        Components::TaskCollectFromTarget,
                        Components::Waypoints
                    >(entity);

                }

                if (!clicksResource) {
                    auto location = cursor - (entity == leader ? Engine::Vector2{} : Engine::Vector2{ Engine::Random::range(-50.0f, 50.0f), Engine::Random::range(-50.0f, 50.0f) });
                    tasks.push_back(Task{ ACTION::MOVE, location });
                } else {
                    tasks.push_back(Task{ ACTION::MOVE_TO_TARGET, target: resource });
                    tasks.push_back(Task{ ACTION::COLLECT, target: resource });
                }
            }
        }

        Systems::TaskQueueSystem(registry);
        Systems::MoveTaskSystem(registry, deltatime);

        Systems::render(registry);
        if (input.mouse.rect.size.x) Engine::Render::stroke(input.mouse.rect, COLOR_ORANGE);


        registry.view<Components::Animation>().each([deltatime](auto& animation) {
            if (!(*animation.animations)[animation.current].size()) return;

            animation.elapsed += deltatime;
            if (animation.elapsed >= animation.frameTime) {
                animation.frame = (animation.frame + 1) % (*animation.animations)[animation.current].size();
                animation.elapsed = 0;
            }
        });

        registry.view<Components::Direction, Components::Animation>().each([deltatime](auto& direction, auto& animation) {
            if (fabs(direction.x) > fabs(direction.y)) {
                if (direction.x > 0) animation.current = "walk_right";
                else if (direction.x < 0) animation.current = "walk_left";
            } else {
                if (direction.y > 0) animation.current = "walk_down";
                else if (direction.y < 0) animation.current = "walk_up";
            }
        });

        registry.view<Components::Animation>(entt::exclude<Components::Direction>).each([deltatime](auto& animation) {
            animation.current = "idle";
        });

    }, (1000/60), NULL);

    Engine::close();
    return 0;
}
