#ifdef RAYLIB
#include "../render.hpp"

#include <functional>
#include <sstream>
#include <raylib.h>
#include "../vector2.hpp"
#include "../rectangle.hpp"
#include "../triangle.hpp"
#include "../ellipse.hpp"
#include "../texture.hpp"
#include "../sprite.hpp"

namespace Engine {
    namespace Render {
        namespace {
            RenderTexture2D layers[Engine::Render::Layer::size];

            Engine::Color blank = COLOR_BLANK;
            Engine::Color white = COLOR_WHITE;
        }

        void layer(Engine::Render::Layer layer, std::function<void()> fn) {
            BeginTextureMode(layers[(char)layer]);
            fn();
            EndTextureMode();
        }

        bool isRunning() {
            return !WindowShouldClose();
        }

        void init(short w, short h, const char* title) {
            InitWindow(w, h, title);

            for (auto& layer : layers) {
                layer = LoadRenderTexture(w, h);
            }
        }

        void close() {
            for (auto& layer : layers) {
                UnloadRenderTexture(layer);
            }
            CloseWindow();
        }

        void frame() {
            BeginDrawing();
            ClearBackground((::Color&)white);

            for (auto& layer : layers) {
                DrawTextureRec(
                    layer.texture,
                    (::Rectangle){ 0, 0, (float)layer.texture.width, (float)-layer.texture.height },
                    (::Vector2){ 0, 0 },
                    (::Color&)white
                );

                BeginTextureMode(layer);
                ClearBackground((::Color&)blank);
                EndTextureMode();
            }

            EndDrawing();
        }

        void projection(Engine::Camera2D& camera, std::function<void()> frame) {
            BeginMode2D((::Camera2D&)camera);
            frame();
            EndMode2D();
        }

        void clearBackground(Engine::Color color) {
            ClearBackground((::Color&)color);
        }

        void text(const char* str, int x, int y, int size, Engine::Color color) {
            DrawText(str, x, y, size, (::Color&)color);
        }

        void text(const char* str, Engine::Vector2 vec, int size, Engine::Color color) {
            text(str, vec.x, vec.y, size, color);
        }

        void text(Engine::Vector2 vec, int x, int y, int size, Engine::Color color) {
            std::ostringstream str;
            str << "x: " << vec.x << " / y: " << vec.y;
            DrawText(str.str().c_str(), x, y, size, (::Color&)color);
        }

        void stroke(Engine::Rectangle& rect, Engine::Color color) {
            DrawRectangleLines(rect.point.x, rect.point.y, rect.size.x, rect.size.y, (::Color&)color);
        }

        void stroke(Engine::Triangle& triangle, Engine::Color color) {
            DrawTriangleLines((::Vector2&)triangle.p1, (::Vector2&)triangle.p2, (::Vector2&)triangle.p3, (::Color&)color);
        }

        void line(Engine::Vector2& a, Engine::Vector2& b, Engine::Color color) {
            DrawLineV((::Vector2&)a, (::Vector2&)b, (::Color&)color);
        }

        void draw(int x, int y, int w, int h, Engine::Color color) {
            DrawRectangle(x, y, w, h, (::Color&)color);
        }

        void draw(Engine::Triangle& triangle, Engine::Color color) {
            DrawTriangle((::Vector2&)triangle.p3, (::Vector2&)triangle.p2, (::Vector2&)triangle.p1, (::Color&)color);
        }

        void draw(const Engine::Ellipse& ellipse, const Engine::Color color) {
            DrawEllipse(
                ellipse.center.x,
                ellipse.center.y,
                ellipse.radius.x,
                ellipse.radius.y,
                (::Color&)color
            );
        }


        // TEXTURES AND SPRITES

        void draw(Engine::Texture& texture, Engine::Vector2 position, Engine::Color color) {
            DrawTexture(
                (::Texture2D&)texture,
                position.x,
                position.y,
                (::Color&)color
            );
        }

        void draw(Engine::Texture& texture, Engine::Rectangle source, Engine::Vector2 position, Engine::Color color) {
            DrawTextureRec(
                (::Texture2D&)texture,
                (::Rectangle&)source,
                (::Vector2&)position,
                (::Color&)color
            );
        }

        void draw(Engine::Sprite& sprite, int frame, Engine::Vector2 position, Engine::Color color) {
            DrawTextureRec(
                (::Texture2D&)sprite.texture,
                ::Rectangle{
                    sprite.frameSize.x * (frame % (int)sprite.frames.x),
                    sprite.frameSize.y * (int)(frame / sprite.frames.x),
                    sprite.frameSize.x,
                    sprite.frameSize.y
                },
                (::Vector2&)position,
                (::Color&)color
            );
        }

        void draw(Engine::Sprite& sprite, int frame, Engine::Vector2 position, Engine::Vector2 dimensions, Engine::Color color) {
            DrawTexturePro(
                    // Texture2D texture,
                (::Texture2D&)sprite.texture,
                    // Rectangle source,
                ::Rectangle{
                    sprite.frameSize.x * (frame % (int)sprite.frames.x),
                    sprite.frameSize.y * (int)(frame / sprite.frames.x),
                    sprite.frameSize.x,
                    sprite.frameSize.y
                },
                    // Rectangle dest,
                ::Rectangle{
                    (int)position.x,
                    (int)position.y,
                    (int)dimensions.x,
                    (int)dimensions.y
                },
                    // Vector2 origin,
                ::Vector2{0.0f, 0.0f},
                    // float rotation,
                0.0f,
                    // Color tint
                (::Color&)color
            );

        }

    }
}
#endif
