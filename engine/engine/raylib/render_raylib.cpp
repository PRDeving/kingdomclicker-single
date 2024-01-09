#ifdef RAYLIB
#include "../render.hpp"

#include <functional>
#include <sstream>
#include <raylib.h>
#include "../vector2.hpp"
#include "../rectangle.hpp"

::Color toRaylib(Engine::Color color) {
    ::Color ret;
    ret.r = color.r;
    ret.g = color.g;
    ret.b = color.b;
    ret.a = color.a;
    return ret;
}

namespace Engine {
    namespace Render {
        bool isRunning() {
            return !WindowShouldClose();
        }

        void init(short w, short h, const char* title) {
            InitWindow(w, h, title);
        }

        void close() {
            CloseWindow();
        }

        void frame(std::function<void()> frame) {
            BeginDrawing();
            frame();
            EndDrawing();
        }

        void frame(Engine::Camera2D& camera, std::function<void()> frame) {
            BeginDrawing();
            projection(camera, frame);
            EndDrawing();
        }

        void projection(Engine::Camera2D& camera, std::function<void()> frame) {
            BeginMode2D((::Camera2D&)camera);
            frame();
            EndMode2D();
        }

        void clearBackground(Engine::Color color) {
            ClearBackground(toRaylib(color));
        }

        void text(const char* str, int x, int y, int size, Engine::Color color) {
            DrawText(str, x, y, size, toRaylib(color));
        }
        void text(Engine::Vector2 vec, int x, int y, int size, Engine::Color color) {
            std::ostringstream str;
            str << "x: " << vec.x << " / y: " << vec.y;
            DrawText(str.str().c_str(), x, y, size, toRaylib(color));
        }

        void stroke(Engine::Rectangle rect, Engine::Color color) {
            DrawRectangleLines(rect.point.x, rect.point.y, rect.size.x, rect.size.y, toRaylib(color));
        }

        void draw(int x, int y, int w, int h, Engine::Color color) {
            DrawRectangle(x, y, w, h, toRaylib(color));
        }
    }
}
#endif
