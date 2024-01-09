#pragma once
#include <functional>
#include "vector2.hpp"
#include "rectangle.hpp"
#include "camera.hpp"
#include "color.hpp"

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
        void text(Engine::Vector2 vec, int x, int y, int size, Engine::Color color);

        void stroke(Engine::Rectangle rect, Engine::Color color);

        void draw(int x, int y, int w, int h, Engine::Color color);
    }
}
