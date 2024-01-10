#pragma once

#include "texture.hpp"

namespace Engine {
    struct Sprite {
        Texture& texture;
        Vector2 frames;
        Vector2 frameSize;

        Sprite(Texture& t, Vector2 f) : texture(t), frames(f) {
            frameSize.x = t.width / f.x;
            frameSize.y = t.height / f.y;
        }
    };
}
