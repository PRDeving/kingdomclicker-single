#pragma once 

#include <vector>
#include <engine/engine.hpp>

namespace Island {
    struct Island {
        unsigned int width, height;
        std::vector<int> map;
        Engine::IA::Navmesh navmesh;
    };

    Island generate(const unsigned int width, const unsigned int height);
}
