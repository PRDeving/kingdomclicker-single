#include "./render.hpp"
#include <sstream>
#include <entt/entt.hpp>
#include <engine/engine.hpp>
#include "../components/components.hpp"

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
                auto collecting = registry.view<Components::TaskCollectFromTarget>();

                registry.view<Components::Resource, Components::Storage, Components::Position>().each([](auto& resource, auto& storage, auto& position) {
                    std::ostringstream txt;
                    txt << std::to_string(storage.amount).c_str() << "/" << std::to_string(storage.capacity).c_str();
                    Engine::Render::text(txt.str().c_str(), position.x - 20, position.y - 20, 10, COLOR_BLACK);
                    Engine::Render::draw(position.x - 5, position.y - 5, 10, 10, COLOR_GREEN);
                });

                registry.view<Components::Position, Components::Scale, Components::Sprite, Components::Animation>().each([&collecting](auto entity, auto& position, auto& scale, auto& sprite, auto& animation) {
                    if (!(*animation.animations)[animation.current].size()) return;
                    int frame = (*animation.animations)[animation.current][animation.frame];
                    Engine::Render::draw(sprite, frame, position - scale / 2, scale, COLOR_WHITE);
                    if (collecting.contains(entity)) Engine::Render::text("collecting", position.x - 20, position.y - 20, 10, COLOR_BLACK);
                });
            });
        });
    }

}
