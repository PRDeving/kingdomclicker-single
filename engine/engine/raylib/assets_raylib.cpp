#ifdef RAYLIB

#include "../assets.hpp"
#include "../texture.hpp"
#include <vector>
#include <raylib.h>

namespace Engine {
    namespace Assets {
        namespace {
            std::vector<Texture2D> textures;
        }

        namespace Texture {
            Engine::Texture load(const char* image) {
                Image img = LoadImage(image);
                Texture2D rtexture = LoadTextureFromImage(img);
                UnloadImage(img);
                textures.push_back(rtexture);

                return Engine::Texture{
                    rtexture.id,
                    rtexture.width,
                    rtexture.height,
                    rtexture.mipmaps,
                    rtexture.format
                };
            }
        }

        void close() {
            for (auto texture : textures) UnloadTexture(texture);
        }
    }
}
#endif
