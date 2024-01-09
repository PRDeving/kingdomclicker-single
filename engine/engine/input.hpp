#pragma once
#include "vector2.hpp"
#include "rectangle.hpp"

namespace Engine {
    namespace Input {
        enum class Button {
            LEFT    = 0x01,
            RIGHT   = 0x02,
        };

        enum class Key {
            LEFT    = 0x01,
            RIGHT   = 0x02,
            UP      = 0x04,
            DOWN    = 0x08,
            SHIFT   = 0x0F,
        };

        struct Mouse {
            Engine::Vector2 cursor;
            Engine::Vector2 p0;
            Engine::Rectangle rect;
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
