#pragma once
#include <functional>
#include "vector2.hpp"
#include "rectangle.hpp"
#include "triangle.hpp"
#include "ellipse.hpp"
#include "camera.hpp"
#include "color.hpp"
#include "texture.hpp"
#include "sprite.hpp"

namespace Engine {
    namespace Render {
        enum Layer {
            L0,
            L1,
            L2,
            L3,
            L4,
            size,
        };


        bool isRunning();
        void init(short w, short h, const char* title);
        void close();

        void layer(Engine::Render::Layer layer, std::function<void()> fn);
        void frame();
        void projection(Engine::Camera2D& camera, std::function<void()> frame);

        void clearBackground(Engine::Color color);
        void text(const char* str, int x, int y, int size, Engine::Color color);
        void text(const char* str, Engine::Vector2 vec, int size, Engine::Color color);
        void text(Engine::Vector2 vec, int x, int y, int size, Engine::Color color);

        void line(Engine::Vector2& a, Engine::Vector2& b, Engine::Color color);

        void stroke(Engine::Rectangle& rect, Engine::Color color);
        void stroke(Engine::Triangle& triangle, Engine::Color color);

        void draw(int x, int y, int w, int h, Engine::Color color);
        void draw(Engine::Triangle& triangle, Engine::Color color);
        void draw(const Engine::Ellipse& ellipse, const Engine::Color color);

        // Textures
        void draw(Engine::Texture& texture, Engine::Vector2 position, Engine::Color color);
        void draw(Engine::Texture& texture, Engine::Rectangle source, Engine::Vector2 position, Engine::Color color);

        // Sprites
        void draw(Engine::Sprite& sprite, int frame, Engine::Vector2 position, Engine::Color color);
        void draw(Engine::Sprite& sprite, int frame, Engine::Vector2 position, Engine::Vector2 dimensions, Engine::Color color);
    }
}
