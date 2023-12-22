#include <cmath>
#include <entt/entt.hpp>
#include <raylib.h>
#include <engine/engine.hpp>
#include "../components/components.hpp"

namespace Systems {
    void render(entt::registry &registry);
    void cameraUpdate(entt::registry &registry, Camera2D& camera, Engine::Input::Input& input, float deltatime);

    void HoverSystem(entt::registry& registry, Engine::Input::Input& input, Camera2D& camera);
    void SelectionSystem(entt::registry& registry, Engine::Input::Input& input);

    void PathfindingSystem(entt::registry& registry, float deltatime);
    void MovementSystem(entt::registry& registry, float deltatime);
    void CollisionSystem(entt::registry& registry);

    void CollectionSystem(entt::registry& registry);

    // TASK SYSTEMS
    void TaskQueueSystem(entt::registry& registry);
    void MoveTaskSystem(entt::registry& registry, float deltatime);
    void FollowTaskSystem(entt::registry& registry);
}
