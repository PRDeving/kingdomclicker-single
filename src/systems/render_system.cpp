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
};

namespace Systems {

    void render(entt::registry &registry){
        
        std::vector<Drawable> drawable;

        registry.view<Components::Position, Components::Scale, Components::Sprite, Components::Animation>().each([&drawable](auto entity, auto& position, auto& scale, auto& sprite, auto& animation) {
            if (!(*animation.animations)[animation.current].size()) return;

            int frame = (*animation.animations)[animation.current][animation.frame];
            drawable.push_back(Drawable{&position, &scale, &sprite, static_cast<char>(frame)});
        });

        std::sort(drawable.begin(), drawable.end(), [](Drawable a, Drawable b) {
            return a.position->y < b.position->y;
        });


        auto& camera = registry.ctx().get<Engine::Camera2D>();

        Engine::Render::layer(Engine::Render::Layer::L0, [&registry, &camera]() {
            Engine::Render::projection(camera, [&registry]() {
                registry.view<Components::Position, Components::Scale, Components::Selected>().each([](auto& position, auto& scale) {
                    auto el = Engine::Ellipse{
                        position  - (scale / 2) + Engine::Vector2{ 16, 30 },
                        { 16, 10 }
                    };

                    Engine::Render::draw(el, COLOR_YELLOW);
                });
            });
        });

        Engine::Render::layer(Engine::Render::Layer::L1, [&camera, &drawable]() {
            Engine::Render::projection(camera, [&drawable]() {
                for (Drawable unit : drawable) {
                    auto pos = *unit.position - *unit.scale / 2;
                    Engine::Render::draw(*unit.sprite, unit.frame, pos, *unit.scale, COLOR_WHITE);
                }
            });
        });

        Systems::renderUI(registry);
        Systems::renderDebug(registry);
    }

}
