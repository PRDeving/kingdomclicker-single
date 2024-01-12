#pragma once

#include "texture.hpp"

namespace Engine {
    struct Sprite {
        Texture& texture;
        Vector2 frames;
        Vector2 frameSize;
        Vector2 offset;

        Sprite(Texture& t, Vector2 f) : texture(t), frames(f) {
            frameSize.x = t.width / f.x;
            frameSize.y = t.height / f.y;
        }

        Sprite(Texture& t, Vector2 f, Vector2 o) : texture(t), frames(f) {
            frameSize.x = t.width / f.x;
            frameSize.y = t.height / f.y;
            offset = o;
        }
    };
}
