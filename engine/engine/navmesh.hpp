#pragma once

#include <earcut.hpp>
#include "polygon.hpp"
#include "triangle.hpp"

namespace Engine {
    namespace IA {
        struct Navmesh {
            Polygon vertices;
            std::vector<Polygon> obstacles;
            std::vector<uint32_t> indices;
            std::vector<Triangle> triangles;
            std::vector<std::vector<int>> neighbors;
        };

        namespace Navigation {
            void compute(std::vector<Polygon>& polygons, Navmesh* mesh);
        }

    }
}
