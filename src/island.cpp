#include "island.hpp"
#include <vector>
#include <iostream>
#include <engine/engine.hpp>

namespace Island {

    bool IsShore(const Island& island, Engine::Vector2& p) {
        return (
            island.map[p.y * island.width + p.x] == 6 && (
                island.map[(p.y - 1) * island.width + p.x - 1] == 0
                || island.map[(p.y - 1) * island.width + p.x] == 0
                || island.map[(p.y - 1) * island.width + p.x + 1] == 0
                || island.map[p.y * island.width + p.x - 1] == 0
                || island.map[p.y * island.width + p.x + 1] == 0
                || island.map[(p.y + 1) * island.width + p.x - 1] == 0
                || island.map[(p.y + 1) * island.width + p.x] == 0
                || island.map[(p.y + 1) * island.width + p.x + 1] == 0
            )
       );
    }

    std::vector<Engine::Vector2> perimeter(const Island& island, const Engine::Vector2& start) {
        std::vector<Engine::Vector2> path;
        std::vector<std::vector<bool>> visited(island.height, std::vector<bool>(island.width, false));

        int dx[] = {0, 1, 0, -1, -1, 1, 1, -1};
        int dy[] = {-1, 0, 1, 0, -1, -1, 1, 1};

        Engine::Vector2 current = start;
        Engine::Vector2 next;

        do {
            path.push_back(current);

            bool foundNext = false;
            for (int i = 0; i < 8; ++i) {
                next = {current.x + dx[i], current.y + dy[i]};
                if (visited[next.y][next.x]) continue;

                visited[next.y][next.x] = true;

                if (IsShore(island, next)) {
                    foundNext = true;
                    break;
                }
            }

            if (!foundNext) break;

            current = next;
        } while (!(current.x == start.x && current.y == start.y)); // Termina cuando regresas al punto de inicio

        return path;
    }

    Island generate(const unsigned int width, const unsigned int height) {
        Island island{ width, height };
        island.map.assign(width * height, 0);

        float centerX = width / 2.0f;
        float centerY = height / 2.0f;
        float maxDistance = sqrt(centerX * centerX + centerY * centerY);

        for (int y = 0; y < height; ++y) {
            for (int x = 0; x < width; ++x) {
                float distance = sqrt((x - centerX) * (x - centerX) + (y - centerY) * (y - centerY));
                float height = maxDistance - distance;

                if (height > maxDistance / 2) {
                    island.map[y * width + x] = 6;
                } else {
                    island.map[y * width + x] = 0;
                }
            }
        }

        Engine::Vector2 initial{ 0, 0 };
        while(!IsShore(island, initial)) {
            initial = initial + Engine::Vector2{ 1, 1 };
        }

        auto coast = perimeter(island, initial);

        Engine::Polygon perimeter;

        Engine::Vector2 dir;
        for(int i = 0; i < coast.size() - 1; i++) {
            Engine::Vector2 d = coast[i+1] - coast[i];
            if (dir == d) continue;

            dir = d;
            perimeter.push_back(Engine::Vector2{
                coast[i].x * 32.0f,
                coast[i].y * 32.0f,
            });
        }

        std::vector<Engine::Polygon> polygons{ perimeter };

        for (int i = 0; i < 3; i++) {
            auto x = Engine::Random::range<float>((centerX * 32) - 200, (centerX * 32) + 200);
            auto y = Engine::Random::range<float>((centerY * 32) - 200, (centerY * 32) + 200);
            polygons.push_back({
                { x + 0, y + 0},
                { x + 50, y + 0},
                { x + 50, y + 50},
                { x + 0, y + 50}
            });
        }

        Engine::IA::Navigation::compute(polygons, &island.navmesh);

        return island;
    }

}
