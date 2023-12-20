#pragma once
#include <functional>

namespace Engine {
    namespace Render {
        bool isRunning();
        void init(short w, short h, const char* title);
        void close();
        void draw(std::function<void()> frame);
    }
}
