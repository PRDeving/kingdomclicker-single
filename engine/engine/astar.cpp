#include "astar.hpp"

#include <vector>
#include <queue>
#include <unordered_set>
#include <unordered_map>
#include <cmath>
#include <algorithm>
#include <iostream>

#include "vector2.hpp"
#include "line.hpp"
#include "navmesh.hpp"
#include "physics.hpp"

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

        namespace Navigation {

            int findTriangleForPoint(const Navmesh& navmesh, const Engine::Vector2& point) {
                for (size_t i = 0; i < navmesh.triangles.size(); ++i) {
                    const Triangle& tri = navmesh.triangles[i];
                    if (Engine::Physics::collides(point, tri)) {
                        return i;  // Índice del triángulo que contiene el punto
                    }
                }
                return -1;  // No se encontró ningún triángulo que contenga el punto
            }

            std::vector<int> path(Engine::IA::Navmesh& navmesh, int startTriangle, int goalTriangle) {
                std::priority_queue<AStarNode, std::vector<AStarNode>, std::greater<AStarNode>> openSet;
                std::unordered_set<int> closedSet;
                std::unordered_map<int, AStarNode> nodesMap;

                AStarNode startNode = {startTriangle, 0, heuristic(
                    Engine::Physics::center(navmesh.triangles[startTriangle]),
                    Engine::Physics::center(navmesh.triangles[goalTriangle])
                ), -1};
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

                        float tentativeGCost = currentNode.gCost + heuristic(Engine::Physics::center(navmesh.triangles[currentNode.triangleIndex]), Engine::Physics::center(navmesh.triangles[neighborIndex]));
                        if (nodesMap.find(neighborIndex) != nodesMap.end() && tentativeGCost >= nodesMap[neighborIndex].gCost) {
                            continue; // No es un mejor camino
                        }

                        AStarNode neighborNode = {neighborIndex, tentativeGCost, heuristic(Engine::Physics::center(navmesh.triangles[neighborIndex]), Engine::Physics::center(navmesh.triangles[goalTriangle])), currentNode.triangleIndex};
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
                    ret.push_back(Engine::Physics::center(navmesh.triangles[idx]));
                }
                ret.push_back(_end);
                            
                return ret;
            }

        }
    }
}
