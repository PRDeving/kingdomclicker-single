#pragma once

#include "../vector2.hpp"
#include "../polygon.hpp"

namespace mapbox {
    namespace util {

        template <>
        struct nth<0, Engine::Vector2> {
            inline static auto get(const Engine::Vector2 &t) {
                return t.x;
            };
        };
        template <>
        struct nth<1, Engine::Vector2> {
            inline static auto get(const Engine::Vector2 &t) {
                return t.y;
            };
        };

    }
}
