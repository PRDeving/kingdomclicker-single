#include "animation.hpp"
#include "../components/components.hpp"

namespace Systems {
    void AnimationSystem(entt::registry& registry, float deltatime) {

        registry.view<Components::Animation>().each([deltatime](auto& animation) {
            if (!(*animation.animations)[animation.current].size()) return;

            animation.elapsed += deltatime;
            if (animation.elapsed >= animation.frameTime) {
                animation.frame = (animation.frame + 1) % (*animation.animations)[animation.current].size();
                animation.elapsed = 0;
            }
        });

    }
}
