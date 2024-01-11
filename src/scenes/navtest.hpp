#pragma once

#include <engine/engine.hpp>
#include <raylib.h>

namespace Scenes {
    class Game : public Engine::Scenes::Scene {

    private:
        Engine::IA::Navmesh navmesh;

    public:

        Game() {
            std::vector<Engine::Polygon> polygons{
                {{100, 10}, {100, 100}, {10, 100}, {10, 10}},
                {{75, 25}, {75, 75}, {25, 75}, {25, 25}}
            };

            Engine::IA::Navigation::compute(polygons, &navmesh);
        }

        void setup() {
        }

        void fixedUpdate(float deltatime) {
        }

        void update(float deltatime) {
        }

        void draw(float deltatime) {
            Engine::Render::frame([this]() {
                Engine::Render::clearBackground(COLOR_WHITE);

                for (auto& triangle : navmesh.triangles) {
                    Engine::Render::stroke(triangle, COLOR_GREEN);
                }
            });
        }

        static Game* getInstance() {
            static Game instance;
            return &instance;
        }
    };
}
