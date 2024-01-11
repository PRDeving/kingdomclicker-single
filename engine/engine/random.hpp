#pragma once
#include <random>

namespace Engine {
    namespace Random {
        typedef std::mt19937 Rng;

        namespace {
            Rng rng;
        }

        void seed(const unsigned long int s);

        template <typename T>
        T range(const T min, const T max) {
            std::uniform_real_distribution<T> dist(min, max);
            return dist(rng);
        }

        template <typename T>
        T range(Rng r, const T min, const T max) {
            std::uniform_real_distribution<T> dist(min, max);
            return dist(r);
        }
    }
}
