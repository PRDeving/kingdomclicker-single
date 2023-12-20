#include <cmath>
#include <entt/entt.hpp>
#include <raylib.h>
#include <engine/engine.hpp>
#include "../components.hpp"

namespace Systems {
    void render(entt::registry &registry);
    void cameraUpdate(entt::registry &registry, Camera2D& camera, Engine::Input::Input& input, float deltatime);
    void SelectionSystem(entt::registry& registry, Engine::Input::Input& input, Camera2D& camera);
    void WaypointSystem(entt::registry& registry, Engine::Input::Input& input, Vector2& cursor, float deltatime);
    void MovementSystem(entt::registry& registry, float deltatime);
}
