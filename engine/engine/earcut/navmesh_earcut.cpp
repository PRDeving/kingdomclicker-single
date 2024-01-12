#include "../navmesh.hpp"
#include "navmesh_earcut.hpp"
#include <earcut.hpp>
#include "../polygon.hpp"

namespace Engine {
    namespace IA {
        namespace Navigation {

            bool shareEdge(const Engine::Vector2& a1, const Engine::Vector2& a2, const Engine::Vector2& b1, const Engine::Vector2& b2) {
                return (a1 == b1 && a2 == b2) || (a1 == b2 && a2 == b1);
            }

            bool areNeighbors(const Engine::Triangle& t1, const Engine::Triangle& t2) {
                return (
                    (shareEdge(t1.p1, t1.p2, t2.p1, t2.p2) || shareEdge(t1.p1, t1.p2, t2.p2, t2.p3) || shareEdge(t1.p1, t1.p2, t2.p3, t2.p1))
                    || (shareEdge(t1.p2, t1.p3, t2.p1, t2.p2) || shareEdge(t1.p2, t1.p3, t2.p2, t2.p3) || shareEdge(t1.p2, t1.p3, t2.p3, t2.p1))
                    || (shareEdge(t1.p3, t1.p1, t2.p1, t2.p2) || shareEdge(t1.p3, t1.p1, t2.p2, t2.p3) || shareEdge(t1.p3, t1.p1, t2.p3, t2.p1))
                );
            }

            void compute(std::vector<Engine::Polygon>& polygons, Engine::IA::Navmesh* mesh) {
                mesh->obstacles = polygons;
                mesh->obstacles.erase(mesh->obstacles.begin());
                mesh->indices = mapbox::earcut<uint32_t>(polygons);
                
                for (const Engine::Polygon& poly : polygons) {
                    for (const auto& vertex : poly) {
                        mesh->vertices.push_back(vertex);
                    }
                }

                for (int i = 0; i < mesh->indices.size(); i += 3) {
                    mesh->triangles.push_back(Engine::Triangle{
                        mesh->vertices[mesh->indices[i]],
                        mesh->vertices[mesh->indices[i + 1]],
                        mesh->vertices[mesh->indices[i + 2]],
                    });
                }

                mesh->neighbors.resize(mesh->indices.size() / 3);
                for (int i = 0; i < mesh->triangles.size(); ++i) {
                    for (int j = i + 1; j < mesh->triangles.size(); ++j) {
                        if (areNeighbors(mesh->triangles[i], mesh->triangles[j])) {
                            mesh->neighbors[i].push_back(j);
                            mesh->neighbors[j].push_back(i);
                        }
                    }
                }
            }

        }

    }
}
