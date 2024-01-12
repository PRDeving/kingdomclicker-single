#include <engine/engine.hpp>

// #include "scenes/splash.hpp"
#include "scenes/game.hpp"

int main() {
    Engine::init("Raid", 1000, 800);

    // Engine::Scenes::load(Scenes::Splash::getInstance());
    Engine::Scenes::load(Scenes::Game::getInstance());

    Engine::loop([](float deltatime) {
        Engine::Scenes::fixedUpdate(16.0f);
        Engine::Scenes::update(deltatime);
        Engine::Scenes::draw(deltatime);
    }, (1000/60), NULL);

    Engine::close();
    return 0;
}
