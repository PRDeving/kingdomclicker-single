#include <raylib.h>
#include <entt/entt.hpp>
#include "systems.hpp"
#include "../components.hpp"

namespace Systems {
    void cameraUpdate(entt::registry &registry) {
        registry.view<Components::Camera, Components::Position>().each([](auto& camera, auto& position) {
            camera.target = (Vector2){ position.x, position.y };
            camera.rotation = 0.0f;
            camera.zoom = 1.0f;
        });
    }
}
