#pragma once
#include <functional>
#include <raylib.h>

// Raylib -> engine bindings
#define COLOR_WHITE RAYWHITE
#define COLOR_BLACK BLACK
namespace Engine {
    typedef Color Color;
    typedef Camera2D Camera2D;
}
// END

namespace Engine {
    namespace Render {
        bool isRunning();
        void init(short w, short h, const char* title);
        void close();

        void frame(std::function<void()> frame);
        void frame(Engine::Camera2D& camera, std::function<void()> frame);
        void projection(Engine::Camera2D& camera, std::function<void()> frame);

        void clearBackground(Engine::Color color);
        void text(const char* str, int x, int y, int size, Engine::Color color);
        void text(Vector2 vec, int x, int y, int size, Engine::Color color);

        void stroke(int x, int y, int w, int h, Engine::Color color);
    }
}
