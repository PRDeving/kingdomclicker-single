#pragma once

#include <entt/entt.hpp>
#include <engine/engine.hpp>

namespace Systems {
    void SelectionSystem(entt::registry& registry, Engine::Input::Input& input);
}
