#include "camera_update.hpp"
#include <entt/entt.hpp>
#include <engine/engine.hpp>
#include "../components/components.hpp"

namespace Systems {
    void cameraUpdate(entt::registry &registry, Engine::Camera2D& camera, Engine::Input::Input& input, float deltatime) {
        registry.view<Components::Camera, Components::Position>().each([&camera, &input, &deltatime](auto& position) {
            position.x += ((+!!(input.keyboard.down & (char)Engine::Input::Key::RIGHT) - +!!(input.keyboard.down & (char)Engine::Input::Key::LEFT))) * deltatime;
            position.y += ((+!!(input.keyboard.down & (char)Engine::Input::Key::DOWN) - +!!(input.keyboard.down & (char)Engine::Input::Key::UP))) * deltatime;

            camera.target = position;
            camera.rotation = 0.0f;
            camera.zoom = 1.0f;
        });
    }
}
