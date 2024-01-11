#pragma once

#include <stack>

namespace Engine {

    namespace Scenes {

        class Scene {
            public:
                virtual void setup() = 0;
                virtual void fixedUpdate(float deltatime) = 0;
                virtual void update(float deltatime) = 0;
                virtual void draw(float deltatime) = 0;
        };

        void pop();
        void load(Scene* scene);
        void fixedUpdate(float deltatime);
        void update(float deltatime);
        void draw(float deltatime);

    }

}
