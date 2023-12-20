#include <raylib.h>
#include "input.hpp"

namespace Engine {
    namespace Input {
        void handle(Input* input) {
            input -> mouse.cursor = GetMousePosition();
            input -> mouse.down = 0;
            if (IsMouseButtonDown(MOUSE_BUTTON_LEFT)) input -> mouse.down |= MOUSE_LEFT;
            if (IsMouseButtonDown(MOUSE_BUTTON_RIGHT)) input -> mouse.down |= MOUSE_RIGHT;
            input -> mouse.pressed = 0;
            if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) input -> mouse.pressed |= MOUSE_LEFT;
            if (IsMouseButtonPressed(MOUSE_BUTTON_RIGHT)) input -> mouse.pressed |= MOUSE_RIGHT;

            input -> keyboard.down = 0;
            if (IsKeyDown(KEY_W)) input->keyboard.down |= KEY_UP;
            if (IsKeyDown(KEY_S)) input->keyboard.down |= KEY_DOWN;
            if (IsKeyDown(KEY_A)) input->keyboard.down |= KEY_LEFT;
            if (IsKeyDown(KEY_D)) input->keyboard.down |= KEY_RIGHT;
        }
    }
}
