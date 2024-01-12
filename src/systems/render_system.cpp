#include "./render.hpp"
#include <sstream>
#include <entt/entt.hpp>
#include <engine/engine.hpp>
#include "../components/components.hpp"

struct Drawable {
    Components::Position* position;
    Components::Scale* scale;
    Components::Sprite* sprite;
    char frame;
    Engine::Color color;
};

namespace Systems {

    void render(entt::registry &registry){
        auto& input = registry.ctx().get<Engine::Input::Input>();
        auto& camera = registry.ctx().get<Engine::Camera2D>();

        Engine::Render::frame([&registry, &input, &camera]() {
            Engine::Render::clearBackground(COLOR_WHITE);

            Engine::Render::text(input.mouse.cursor, 10, 20, 10, COLOR_BLACK);
            Engine::Render::text(camera.target, 10, 10, 10, COLOR_BLACK);

            Engine::Render::projection(camera, [&registry]() {
                auto selected = registry.view<Components::Selected>();

                registry.view<Components::Resource, Components::Storage, Components::Position>().each([](auto& resource, auto& storage, auto& position) {
                    std::ostringstream txt;
                    txt << std::to_string(storage.amount).c_str() << "/" << std::to_string(storage.capacity).c_str();
                    Engine::Render::text(txt.str().c_str(), position.x - 20, position.y - 20, 10, COLOR_BLACK);
                    Engine::Render::draw(position.x - 5, position.y - 5, 10, 10, COLOR_GREEN);
                });

                std::vector<Drawable> drawable;

                registry.view<Components::Position, Components::Scale, Components::Sprite, Components::Animation>().each([&drawable, &selected](auto entity, auto& position, auto& scale, auto& sprite, auto& animation) {
                    if (!(*animation.animations)[animation.current].size()) return;

                    int frame = (*animation.animations)[animation.current][animation.frame];
                    Engine::Color color = selected.contains(entity) ? COLOR_WHITE : COLOR_LIGHTGRAY;
                    drawable.push_back(Drawable{&position, &scale, &sprite, static_cast<char>(frame), color});
                });

                std::sort(drawable.begin(), drawable.end(), [](Drawable a, Drawable b) {
                    return a.position->y < b.position->y;
                });

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

                for (Drawable unit : drawable) {
                    Engine::Render::draw(*unit.sprite, unit.frame, *unit.position - *unit.scale / 2, *unit.scale, unit.color);
                }

            });
        });
    }

}
