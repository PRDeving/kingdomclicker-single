#include "random.hpp"

namespace Engine {
    namespace Random {
        void seed(const unsigned long int s) {
            rng = (std::mt19937)s;
        }
    }
}
