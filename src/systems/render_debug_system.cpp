#include "./render_debug.hpp"

#include <entt/entt.hpp>
#include <engine/engine.hpp>
#include "../components/components.hpp"

namespace Systems {

    void renderDebug(entt::registry &registry){
        Engine::Render::layer(Engine::Render::Layer::L0, [&registry]() {

            auto& camera = registry.ctx().get<Engine::Camera2D>();
            Engine::Render::projection(camera, [&registry]() {
                auto& navmesh = registry.ctx().get<Engine::IA::Navmesh>();

                for (auto& triangle : navmesh.triangles) {
                    Engine::Render::draw(triangle, COLOR_DEBUG);
                    Engine::Render::stroke(triangle, COLOR_GREEN);
                }

                registry.view<Components::Position, Components::Waypoints>().each([](auto& position, auto& waypoints) {
                    Engine::Render::line(position, waypoints[0], COLOR_YELLOW);

                    Engine::Vector2* prev = nullptr;
                    for (int i = 0;  i < waypoints.size(); i++) {
                        Engine::Render::draw(waypoints[i].x - 4, waypoints[i].y - 4, 8, 8, COLOR_YELLOW);
                        if (prev != nullptr) Engine::Render::line(*prev, waypoints[i], COLOR_YELLOW);
                        prev = &waypoints[i];
                    }

                });

                for (Engine::Polygon obstacle : navmesh.obstacles) {
                    for (int i = 1;  i < obstacle.size(); i++) {
                        Engine::Render::line(obstacle[i - 1], obstacle[i], COLOR_RED);
                    }
                    Engine::Render::line(obstacle.back(), obstacle.front(), COLOR_RED);
                }
            });
        });

    }

}
