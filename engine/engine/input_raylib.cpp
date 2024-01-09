#include <cmath>
#include <raylib.h>
#include "input.hpp"

namespace Engine {
    namespace Input {
        void handle(Input* input) {
            auto mouse = GetMousePosition();
            input -> mouse.cursor = Engine::Vector2{mouse.x, mouse.y};
            input -> mouse.down = 0;
            input -> mouse.pressed = 0;
            input -> keyboard.down = 0;

            // MOUSE DOWN

            if (IsMouseButtonDown(MOUSE_BUTTON_LEFT)) input->mouse.down |= MOUSE_LEFT;
            else {
                input->mouse.p0.x = 0;
                input->mouse.p0.y = 0;
                input->mouse.rect.size.x = 0;
                input->mouse.rect.size.y = 0;
                input->mouse.rect.point.x = 0;
                input->mouse.rect.point.y = 0;
            }
            if (IsMouseButtonDown(MOUSE_BUTTON_RIGHT)) input -> mouse.down |= MOUSE_RIGHT;

            // MOUSE PRESSED

            if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
                input -> mouse.pressed |= MOUSE_LEFT;
                input->mouse.p0.x = input->mouse.cursor.x;
                input->mouse.p0.y = input->mouse.cursor.y;
            }

            if (IsMouseButtonPressed(MOUSE_BUTTON_RIGHT)) input -> mouse.pressed |= MOUSE_RIGHT;



            // KEYBOARD
            
            if (input->mouse.p0.x) {
                input->mouse.rect.size.x = abs(input->mouse.p0.x - input->mouse.cursor.x);
                input->mouse.rect.size.y = abs(input->mouse.p0.y - input->mouse.cursor.y);
                input->mouse.rect.point.x = std::min(input->mouse.p0.x, input->mouse.cursor.x);
                input->mouse.rect.point.y = std::min(input->mouse.p0.y, input->mouse.cursor.y);
            }

            if (IsKeyDown(KEY_W)) input->keyboard.down |= KEY_UP;
            if (IsKeyDown(KEY_S)) input->keyboard.down |= KEY_DOWN;
            if (IsKeyDown(KEY_A)) input->keyboard.down |= KEY_LEFT;
            if (IsKeyDown(KEY_D)) input->keyboard.down |= KEY_RIGHT;
            if (IsKeyDown(KEY_LEFT_SHIFT) || IsKeyDown(KEY_RIGHT_SHIFT)) input->keyboard.down |= KEY_SHIFT;
        }
    }
}
