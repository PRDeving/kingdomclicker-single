#include "./render.hpp"
#include <sstream>
#include <entt/entt.hpp>
#include <engine/engine.hpp>
#include "../components/components.hpp"

#include "render_ui.hpp"
#include "render_debug.hpp"

struct Drawable {
    Components::Position* position;
    Components::Scale* scale;
    Components::Sprite* sprite;
    char frame;
    Engine::Color color;
};

namespace Systems {

    void render(entt::registry &registry){
        auto selected = registry.view<Components::Selected>();
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

        Engine::Render::layer(Engine::Render::Layer::L1, [&registry, &drawable]() {
            auto& camera = registry.ctx().get<Engine::Camera2D>();
            Engine::Render::projection(camera, [&drawable]() {
                for (Drawable unit : drawable) {
                    Engine::Render::draw(*unit.sprite, unit.frame, *unit.position - *unit.scale / 2, *unit.scale, unit.color);
                }
            });
        });

        Systems::renderUI(registry);
        Systems::renderDebug(registry);

        Engine::Render::frame();
    }

}
