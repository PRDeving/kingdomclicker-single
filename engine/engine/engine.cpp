#include <chrono>
#include "engine.hpp"

namespace Engine {
    bool isRunning() {
        return Render::isRunning();
    }

    void init(const char* title, const int w, const int h) {
        Engine::Render::init(w, h, title);
        Engine::Random::seed(0);
    }

    void init(const char* title) {
        init(title, 800, 600);
    }

    void close() {
        Engine::Assets::close();
        Engine::Render::close();
    }

    void loop(std::function<void(float)> frame, const float interval, bool* interrupt) {
        auto last = std::chrono::high_resolution_clock::now();
        while(isRunning() && !(!!interrupt && *interrupt)) {
            auto now = std::chrono::high_resolution_clock::now();
            auto deltatime = std::chrono::duration_cast<std::chrono::milliseconds>(now - last);
            if(deltatime.count() < interval) continue;

            frame(deltatime.count());
            last = now;
        }
    }
}
