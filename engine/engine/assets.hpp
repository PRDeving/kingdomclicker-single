#pragma once

#include <string>
#include "texture.hpp"

namespace Engine {
    namespace Assets {
        namespace Texture {
            Engine::Texture load(const char* image);
        }

        void close();
    }
}
