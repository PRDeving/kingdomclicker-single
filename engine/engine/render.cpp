#include <functional>
#include <sstream>
#include <raylib.h>
#include "render.hpp"

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
            BeginMode2D(camera);
            frame();
            EndMode2D();
        }

        void clearBackground(Engine::Color color) {
            ClearBackground(color);
        }

        void text(const char* str, int x, int y, int size, Engine::Color color) {
            DrawText(str, x, y, size, color);
        }
        void text(Vector2 vec, int x, int y, int size, Engine::Color color) {
            std::ostringstream str;
            str << "x: " << vec.x << " / y: " << vec.y;
            DrawText(str.str().c_str(), x, y, size, color);
        }

        void stroke(int x, int y, int w, int h, Engine::Color color) {
            DrawRectangle(x, y, w, h, color);
        }
    }
}
