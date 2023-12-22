#include "../systems.hpp"

namespace Systems {

    void FollowTaskSystem(entt::registry& registry) {
        // CHECK COMPLETION
        registry.view<Components::TaskFollow, Components::TaskMoveTo>().each([&registry](auto entity, auto& follow, auto& move) {
            registry.remove<Components::TaskFollow>(entity);
        });

        // INIT
        auto leaders = registry.view<Components::TaskMoveTo>();
        registry.view<Components::TaskFollow>().each([&registry, &leaders](auto entity, auto& follow) {
            if (!leaders.contains(follow.target)) registry.remove<Components::TaskFollow>(entity);

            auto leaderTarget = leaders.get<Components::TaskMoveTo>(follow.target);

            auto target = (leaderTarget - Vector2{ Engine::Random::range(-50.0f, 50.0f), Engine::Random::range(-50.0f, 50.0f) });
            registry.emplace_or_replace<Components::TaskMoveTo>(entity, target);
        });
    }

}
