#pragma once

#include <engine/engine.hpp>

#include <entt/entt.hpp>
#include <random>
#include <iostream>
#include <cstdlib>

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

        Engine::Texture terrainTexture;
        Engine::Sprite terrainSprite;

        Engine::Texture playerTexture;
        Engine::Sprite playerSprite;

        std::unordered_map<std::string, std::vector<int>> animations;

        int w = 30;
        int h = 30;
        std::vector<int> tilemap;

    public:

        Game() :
            terrainTexture(Engine::Assets::Texture::load("../assets/terrain.png")),
            terrainSprite(terrainTexture, Engine::Vector2{ 3.0f, 3.0f }),

            playerTexture(Engine::Assets::Texture::load("../assets/base.png")),
            playerSprite(playerTexture, Engine::Vector2{ 4.0f, 4.0f })
        {

            animations["idle"] = std::vector<int>{0};
            animations["move_down"] = std::vector<int>{0,1,2,3};
            animations["move_up"] = std::vector<int>{4,5,6,7};
            animations["move_right"] = std::vector<int>{8,9,10,11};
            animations["move_left"] = std::vector<int>{12,13,14,15};
        }

        bool IsLandTile(const std::vector<int>& map, int x, int y, int width, int height) {
            if (x < 0 || y < 0 || x >= width || y >= height) {
                return false;
            }
            return map[y * width + x] == 4;
        }

        std::vector<Engine::Vector2> FollowCoastline(const std::vector<int>& map, int width, int height, const Engine::Vector2& start) {
            std::vector<Engine::Vector2> path;
            int dx[4] = {0, 1, 0, -1}; // Direcciones: Arriba, Derecha, Abajo, Izquierda
            int dy[4] = {-1, 0, 1, 0};

            Engine::Vector2 current = start;
            Engine::Vector2 next;
            int direction = 0; // Comienza mirando hacia arriba

            do {
                path.push_back(current);

                // Encuentra el siguiente tile de costa
                bool foundNext = false;
                for (int i = 0; i < 4; ++i) {
                    next = {current.x + dx[direction], current.y + dy[direction]};
                    if (IsLandTile(map, next.x, next.y, width, height)) {
                        foundNext = true;
                        break;
                    }
                    direction = (direction + 1) % 4; // Cambia a la siguiente dirección
                }

                if (!foundNext) {
                    std::cerr << "Error: No se encontró un camino válido desde (" << current.x << ", " << current.y << ")\n";
                    break;
                }

                current = next;
            } while (!(current.x == start.x && current.y == start.y)); // Termina cuando regresas al punto de inicio

            return path;
        }
    

        void setup() {
            registry.clear();
            registry.ctx().emplace<Engine::Input::Input>();
            registry.ctx().emplace<Engine::Camera2D>(400.0f, 300.0f);

            entt::entity camera_entity = registry.create();
            registry.emplace<Components::Position>(camera_entity, 30.0f, 30.0f);
            registry.emplace<Components::Camera>(camera_entity);
        
            for(int i = 0; i < 8; i++) {
                auto unit = Assamblages::Unit(registry, 110 + 15.0f * i, 100.0f);
                registry.emplace<Components::Sprite>(unit, playerSprite);
                registry.emplace<Components::Animation>(unit, &animations, "idle", (unsigned char)0, 200.0f);
            }

            tilemap.assign(w*h, 4);

            auto initial = Engine::Vector2{ 0, 0 };

            auto coast = FollowCoastline(tilemap, w, h, initial);

            Engine::Polygon perimeter;

            Engine::Vector2 dir;
            for(int i = 0; i < coast.size() - 1; i++) {
                Engine::Vector2 d = coast[i+1] - coast[i];
                if (dir == d) continue;

                dir = d;
                perimeter.push_back(Engine::Vector2{
                    coast[i].x * 32.0f + 16.0f,
                    coast[i].y * 32.0f + 16.0f,
                });
            }

            std::vector<Engine::Polygon> polygons{ perimeter };

            for (int i = 0; i < 18; i++) {
                auto x = Engine::Random::range<float>(50, 900);
                auto y = Engine::Random::range<float>(50, 900);
                polygons.push_back({
                    { x + 0, y + 0},
                    { x + 50, y + 0},
                    { x + 50, y + 50},
                    { x + 0, y + 50}
                });
            }

            registry.ctx().emplace<Engine::IA::Navmesh>();
            auto& navmesh = registry.ctx().get<Engine::IA::Navmesh>();
            Engine::IA::Navigation::compute(polygons, &navmesh);
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
            Engine::Render::layer(Engine::Render::Layer::L0, [this]() {
                auto& camera = registry.ctx().get<Engine::Camera2D>();
                Engine::Render::projection(camera, [this]() {

                for(int i = 0; i < tilemap.size(); i++) {
                    int x = i % w;
                    int y = i / w;
                    Engine::Render::draw(terrainSprite, tilemap[i], Engine::Vector2{x * 32.0f, y * 32.0f}, Engine::Vector2{ 32.0f, 32.0f }, COLOR_GREEN);
                }

                auto& navmesh = registry.ctx().get<Engine::IA::Navmesh>();
                bool first = true;
                for(auto& poly : navmesh.obstacles) {
                    if (!first) Engine::Render::draw(poly[0].x, poly[0].y, 50, 50, COLOR_GRAY);
                    first = false;
                }

                });
            });

            Systems::render(registry);
        }

        static Game* getInstance() {
            static Game instance;
            return &instance;
        }
    };
}
