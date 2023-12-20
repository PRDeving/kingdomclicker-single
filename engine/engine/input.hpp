#pragma once
#include <raylib.h>
#include "render.hpp"

#define MOUSE_LEFT  (char)0x01
#define MOUSE_RIGHT (char)0x02

#define KEY_LEFT    (char)0x01
#define KEY_RIGHT   (char)0x02
#define KEY_UP      (char)0x04
#define KEY_DOWN    (char)0x08
#define KEY_SHIFT   (char)0x0F

namespace Engine {
    namespace Input {

        struct Mouse {
            Vector2 cursor;
            Vector2 p0;
            Rectangle rect;
            char pressed;
            char down;
        };

        struct Keyboard {
            char pressed;
            char down;
        };

        struct Input {
            Mouse mouse;
            Keyboard keyboard;
        };

        void handle(Input* input);
    }
}
