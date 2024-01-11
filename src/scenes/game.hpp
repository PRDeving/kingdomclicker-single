#pragma once

#include <engine/engine.hpp>

#include <entt/entt.hpp>
#include <random>

#include "../components/components.hpp"
#include "../assamblages/assamblages.hpp"

#include "../systems/render.hpp"
#include "../systems/camera_update.hpp"
#include "../systems/hover.hpp"
#include "../systems/selection.hpp"
#include "../systems/pathfinding.hpp"
#include "../systems/movement.hpp"
#include "../systems/collision.hpp"
#include "../systems/animation.hpp"

#include "../systems/tasks/queue.hpp"
#include "../systems/tasks/move.hpp"

namespace Scenes {
    class Game : public Engine::Scenes::Scene {

    private:
        entt::registry registry;

        Engine::Texture playerTexture;
        Engine::Sprite playerSprite;

        std::unordered_map<std::string, std::vector<int>> animations;

    public:

        Game() :
            playerTexture(Engine::Assets::Texture::load("../assets/base.png")),
            playerSprite(playerTexture, Engine::Vector2{ 4.0f, 4.0f }) {

            animations["idle"] = std::vector<int>{0};
            animations["move_down"] = std::vector<int>{0,1,2,3};
            animations["move_up"] = std::vector<int>{4,5,6,7};
            animations["move_right"] = std::vector<int>{8,9,10,11};
            animations["move_left"] = std::vector<int>{12,13,14,15};
        }

        void setup() {
            registry.clear();
            registry.ctx().emplace<Engine::Input::Input>();
            registry.ctx().emplace<Engine::Camera2D>(400.0f, 300.0f);

            entt::entity camera_entity = registry.create();
            registry.emplace<Components::Position>(camera_entity, 30.0f, 30.0f);
            registry.emplace<Components::Camera>(camera_entity);
        
            for(int i = 0; i < 8; i++) {
                auto unit = Assamblages::Unit(registry, 15.0f * i, 10.0f);
                registry.emplace<Components::Sprite>(unit, playerSprite);
                registry.emplace<Components::Animation>(unit, &animations, "idle", (unsigned char)0, 200.0f);
            }
        }

        void fixedUpdate(float deltatime) {
            Systems::PathfindingSystem(registry, deltatime);
            Systems::CollisionSystem(registry, deltatime);
            Systems::MovementSystem(registry, deltatime);
        }

        void update(float deltatime) {
            auto& camera = registry.ctx().get<Engine::Camera2D>();
            auto& input = registry.ctx().get<Engine::Input::Input>();

            Engine::Input::handle(&input);
            Systems::cameraUpdate(registry, camera, input, deltatime);
            Engine::Vector2 cursor = Engine::Camera::screenToWorld(input.mouse.cursor, camera);

            Systems::HoverSystem(registry, input, camera);
            Systems::SelectionSystem(registry, input);
        
            if (input.mouse.pressed & (char)Engine::Input::Button::RIGHT) {
                auto entities = registry.view<Components::Selected, Components::TaskQueue>();
                if (entities.begin() != entities.end()) {
                    entt::entity leader = *entities.begin();

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

                        auto location = cursor - (entity == leader ? Engine::Vector2{} : Engine::Vector2{ Engine::Random::range(-50.0f, 50.0f), Engine::Random::range(-50.0f, 50.0f) });
                        tasks.push_back(Task{ ACTION::MOVE, location });
                    }
                }
            }

            Systems::TaskQueueSystem(registry);
            Systems::MoveTaskSystem(registry, deltatime);

            Systems::AnimationSystem(registry, deltatime);

            registry.view<Components::Direction, Components::Animation>().each([](auto& direction, auto& animation) {
                if (fabs(direction.x) > fabs(direction.y)) {
                    if (direction.x > 0) animation.current = "move_right";
                    else if (direction.x < 0) animation.current = "move_left";
                } else {
                    if (direction.y > 0) animation.current = "move_down";
                    else if (direction.y < 0) animation.current = "move_up";
                }
            });

            registry.view<Components::Animation>(entt::exclude<Components::Direction>).each([](auto& animation) {
                animation.current = "idle";
            });
        }

        void draw(float deltatime) {
            auto& input = registry.ctx().get<Engine::Input::Input>();

            Systems::render(registry);
            if (input.mouse.rect.size.x) Engine::Render::stroke(input.mouse.rect, COLOR_ORANGE);
        }

        static Game* getInstance() {
            static Game instance;
            return &instance;
        }
    };
}
