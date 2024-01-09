#pragma once
#include <entt/entt.hpp>
#include <engine/engine.hpp>

namespace Systems {
    void cameraUpdate(entt::registry &registry, Engine::Camera2D& camera, Engine::Input::Input& input, float deltatime);
}
