#include <functional>
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

        void draw(std::function<void()> frame) {
            BeginDrawing();
            frame();
            EndDrawing();
        }
    }
}
