#include "camera_update.hpp"
#include <entt/entt.hpp>
#include <engine/engine.hpp>
#include "../components/components.hpp"

namespace Systems {
    void cameraUpdate(entt::registry &registry, Engine::Camera2D& camera, Engine::Input::Input& input, float deltatime) {
        registry.view<Components::Camera, Components::Position>().each([&camera, &input, &deltatime](auto& position) {
            position.x += ((+!!(input.keyboard.down & KEY_RIGHT) - +!!(input.keyboard.down & KEY_LEFT))) * deltatime;
            position.y += ((+!!(input.keyboard.down & KEY_DOWN) - +!!(input.keyboard.down & KEY_UP))) * deltatime;

            camera.target = position;
            camera.rotation = 0.0f;
            camera.zoom = 1.0f;
        });
    }
}
