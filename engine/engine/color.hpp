#pragma once

#define COLOR_LIGHTGRAY  Engine::Color{ 200, 200, 200, 255 }
#define COLOR_GRAY       Engine::Color{ 130, 130, 130, 255 }
#define COLOR_DARKGRAY   Engine::Color{ 80, 80, 80, 255 }
#define COLOR_YELLOW     Engine::Color{ 253, 249, 0, 255 }
#define COLOR_GOLD       Engine::Color{ 255, 203, 0, 255 }
#define COLOR_ORANGE     Engine::Color{ 255, 161, 0, 255 }
#define COLOR_PINK       Engine::Color{ 255, 109, 194, 255 }
#define COLOR_RED        Engine::Color{ 230, 41, 55, 255 }
#define COLOR_MAROON     Engine::Color{ 190, 33, 55, 255 }
#define COLOR_GREEN      Engine::Color{ 0, 228, 48, 255 }
#define COLOR_LIME       Engine::Color{ 0, 158, 47, 255 }
#define COLOR_DARKGREEN  Engine::Color{ 0, 117, 44, 255 }
#define COLOR_SKYBLUE    Engine::Color{ 102, 191, 255, 255 }
#define COLOR_BLUE       Engine::Color{ 0, 121, 241, 255 }
#define COLOR_DARKBLUE   Engine::Color{ 0, 82, 172, 255 }
#define COLOR_PURPLE     Engine::Color{ 200, 122, 255, 255 }
#define COLOR_VIOLET     Engine::Color{ 135, 60, 190, 255 }
#define COLOR_DARKPURPLE Engine::Color{ 112, 31, 126, 255 }
#define COLOR_BEIGE      Engine::Color{ 211, 176, 131, 255 }
#define COLOR_BROWN      Engine::Color{ 127, 106, 79, 255 }
#define COLOR_DARKBROWN  Engine::Color{ 76, 63, 47, 255 }

#define COLOR_WHITE      Engine::Color{ 255, 255, 255, 255 }
#define COLOR_BLACK      Engine::Color{ 0, 0, 0, 255 }
#define COLOR_BLANK      Engine::Color{ 0, 0, 0, 0 }
#define COLOR_MAGENTA    Engine::Color{ 255, 0, 255, 255 }

namespace Engine {
    typedef struct Color {
        unsigned char r;
        unsigned char g;
        unsigned char b;
        unsigned char a;
    } Color;
}
