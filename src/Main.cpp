#include <Game.h>
int main(int argc, char* argv[]) {
    Game game;
    game.run();
    sf::Clock clock;
    float dt = 1/180.f;
    float accumulator = .0f;
    while(!game.getWindow()->isDone()) {
        accumulator += clock.getElapsedTime().asSeconds();
        clock.restart();

        while(accumulator >= dt) {

        game.update();
        game.render();
        game.handleInput();
        game.restart();
        accumulator -= dt;
        }
    }
    //astelPrint();
}
