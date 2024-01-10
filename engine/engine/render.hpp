#pragma once
#include <functional>
#include "vector2.hpp"
#include "rectangle.hpp"
#include "camera.hpp"
#include "color.hpp"
#include "texture.hpp"
#include "sprite.hpp"

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

        // Textures
        void draw(Engine::Texture& texture, Engine::Vector2 position, Engine::Color color);
        void draw(Engine::Texture& texture, Engine::Rectangle source, Engine::Vector2 position, Engine::Color color);

        // Sprites
        void draw(Engine::Sprite& sprite, int frame, Engine::Vector2 position, Engine::Color color);
    }
}
