#include "./render_ui.hpp"
#include <entt/entt.hpp>
#include <engine/engine.hpp>

namespace Systems {

    void renderUI(entt::registry &registry){

        Engine::Render::layer(Engine::Render::Layer::L4, [&registry]() {
            auto& input = registry.ctx().get<Engine::Input::Input>();
            auto& camera = registry.ctx().get<Engine::Camera2D>();

            Engine::Render::text(input.mouse.cursor, 10, 20, 10, COLOR_BLACK);
            Engine::Render::text(camera.target, 10, 10, 10, COLOR_BLACK);
            if (input.mouse.rect.size.x) Engine::Render::stroke(input.mouse.rect, COLOR_ORANGE);
        });

    }

}
