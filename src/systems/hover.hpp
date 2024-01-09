#pragma once

#include <entt/entt.hpp>
#include <engine/engine.hpp>

namespace Systems {
    void HoverSystem(entt::registry& registry, Engine::Input::Input& input, Engine::Camera2D& camera);
}
