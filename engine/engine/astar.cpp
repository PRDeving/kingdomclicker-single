#include "astar.hpp"

#include <vector>
#include <queue>
#include <unordered_set>
#include <unordered_map>
#include <cmath>
#include <algorithm>

#include "vector2.hpp"
#include "navmesh.hpp"

namespace Engine {
    namespace IA {

        struct AStarNode {
            int triangleIndex;
            float gCost;
            float hCost;
            int parentIndex;

            float getFCost() const {
                return gCost + hCost;
            }

            bool operator>(const AStarNode& other) const {
                return getFCost() > other.getFCost();
            }
        };

        float heuristic(const Engine::Vector2& a, const Engine::Vector2& b) {
            float dx = b.x - a.x;
            float dy = b.y - a.y;
            return sqrt(dx * dx + dy * dy);
        }

        Engine::Vector2 centroid(const Triangle& triangle) {
            float cx = (triangle.p1.x + triangle.p2.x + triangle.p3.x) / 3.0f;
            float cy = (triangle.p1.y + triangle.p2.y + triangle.p3.y) / 3.0f;
            return {cx, cy};
        }

        bool pointInTriangle(const Engine::Vector2& p, const Engine::Vector2& a, const Engine::Vector2& b, const Engine::Vector2& c) {
            // Calcula vectores
            std::array<float, 2> v0 = {c.x - a.x, c.y - a.y};
            std::array<float, 2> v1 = {b.x - a.x, b.y - a.y};
            std::array<float, 2> v2 = {p.x - a.x, p.y - a.y};

            // Calcula productos punto
            float dot00 = v0[0] * v0[0] + v0[1] * v0[1];
            float dot01 = v0[0] * v1[0] + v0[1] * v1[1];
            float dot02 = v0[0] * v2[0] + v0[1] * v2[1];
            float dot11 = v1[0] * v1[0] + v1[1] * v1[1];
            float dot12 = v1[0] * v2[0] + v1[1] * v2[1];

            // Calcula barycentric coordinates
            float invDenom = 1 / (dot00 * dot11 - dot01 * dot01);
            float u = (dot11 * dot02 - dot01 * dot12) * invDenom;
            float v = (dot00 * dot12 - dot01 * dot02) * invDenom;

            // Verifica si el punto está en el triángulo
            return (u >= 0) && (v >= 0) && (u + v < 1);
        }

        namespace Navigation {

            int findTriangleForPoint(const Navmesh& navmesh, const Engine::Vector2& point) {
                for (size_t i = 0; i < navmesh.triangles.size(); ++i) {
                    const Triangle& tri = navmesh.triangles[i];
                    if (pointInTriangle(point, tri.p1, tri.p2, tri.p3)) {
                        return i;  // Índice del triángulo que contiene el punto
                    }
                }
                return -1;  // No se encontró ningún triángulo que contenga el punto
            }

            std::vector<int> path(Engine::IA::Navmesh& navmesh, int startTriangle, int goalTriangle) {
                std::priority_queue<AStarNode, std::vector<AStarNode>, std::greater<AStarNode>> openSet;
                std::unordered_set<int> closedSet;
                std::unordered_map<int, AStarNode> nodesMap;

                AStarNode startNode = {startTriangle, 0, heuristic(centroid(navmesh.triangles[startTriangle]), centroid(navmesh.triangles[goalTriangle])), -1};
                openSet.push(startNode);
                nodesMap[startTriangle] = startNode;

                while (!openSet.empty()) {
                    AStarNode currentNode = openSet.top();
                    openSet.pop();

                    if (currentNode.triangleIndex == goalTriangle) {
                        std::vector<int> path;
                        while (currentNode.parentIndex != -1) {
                            path.push_back(currentNode.triangleIndex);
                            currentNode = nodesMap[currentNode.parentIndex];
                        }
                        std::reverse(path.begin(), path.end());
                        return path;
                    }

                    closedSet.insert(currentNode.triangleIndex);

                    for (int neighborIndex : navmesh.neighbors[currentNode.triangleIndex]) {
                        if (closedSet.find(neighborIndex) != closedSet.end()) {
                            continue;
                        }

                        float tentativeGCost = currentNode.gCost + heuristic(centroid(navmesh.triangles[currentNode.triangleIndex]), centroid(navmesh.triangles[neighborIndex]));
                        if (nodesMap.find(neighborIndex) != nodesMap.end() && tentativeGCost >= nodesMap[neighborIndex].gCost) {
                            continue; // No es un mejor camino
                        }

                        AStarNode neighborNode = {neighborIndex, tentativeGCost, heuristic(centroid(navmesh.triangles[neighborIndex]), centroid(navmesh.triangles[goalTriangle])), currentNode.triangleIndex};
                        openSet.push(neighborNode);
                        nodesMap[neighborIndex] = neighborNode;
                    }
                }

                return {};
            }

            Path path(Engine::IA::Navmesh& navmesh, Engine::Vector2& _start, Engine::Vector2& _end) {
                int start = findTriangleForPoint(navmesh, _start);
                int end = findTriangleForPoint(navmesh, _end);

                if (start < 0 || end < 0) return {};

                auto indices = path(navmesh, start, end);
                std::vector<Engine::Vector2> ret{ _start };

                for (int idx : indices) {
                    ret.push_back(centroid(navmesh.triangles[idx]));
                }
                ret[ret.size() - 1] = _end;
                return ret;
            }

        }
    }
}
