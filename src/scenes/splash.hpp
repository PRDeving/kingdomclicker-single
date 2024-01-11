#pragma once

#include <engine/engine.hpp>
#include "game.hpp"

namespace Scenes {
    class Splash : public Engine::Scenes::Scene {

    private:
        int loadtime = 1000;
        int elapsed;

    public:

        void setup() {
            elapsed = 0;
        }

        void fixedUpdate(float deltatime) { }

        void update(float deltatime) {
            std::cout << "splash: " << elapsed << std::endl;
            elapsed += deltatime;
            if (elapsed >= loadtime) Engine::Scenes::load(Scenes::Game::getInstance());
        }

        void draw(float deltatime) {
            Engine::Render::frame([]() {
                Engine::Render::clearBackground(COLOR_BLACK);

                Engine::Render::text("loading...", 10, 20, 30, COLOR_WHITE);
            });
        }

        static Splash* getInstance() {
            static Splash instance;
            return &instance;
        }
    };
}
