#include "scene.hpp"

#include <stack>
#include <iostream>

namespace Engine {
    namespace Scenes {

        namespace {
            std::stack<Scene*> scenes;
        }

        void setup() {
            if (scenes.empty()) return;
            scenes.top()->setup();
        }

        void fixedUpdate(float deltatime) {
            if (scenes.empty()) return;
            scenes.top()->fixedUpdate(deltatime);
        }

        void update(float deltatime) {
            if (scenes.empty()) return;
            scenes.top()->update(deltatime);
        }

        void draw(float deltatime) {
            if (scenes.empty()) return;
            scenes.top()->draw(deltatime);
        }

        void pop() {
            scenes.pop();
            setup();
        }

        void load(Scene* scene) {
            scene->setup();
            scenes.push(scene);
        }

    }

}
