#include "Game.h"
#include <iostream>
Game::Game() :
   m_window("Sweepington", sf::Vector2u(960, 512)),
   m_context(&m_window),
   m_master(&m_context, Master::Difficulty::Expert )
{

}

Game::~Game(){}

void Game::run() {
    std::cout << "here 1.." << std::endl;
    restart();
    srand(time(NULL));
    m_elapsed = .0f;
    m_context.registerTexture(Context::Type::Game, "assets/2000.png");
    m_master.build();
}

sf::Time Game::getElapsed() {return m_clock.getElapsedTime();}
void Game::restart() {m_elapsed += m_clock.restart().asSeconds();}
Window* Game::getWindow() {return &m_window;}

void Game::handleInput() {
  sf::Event event;
    while(m_window.getRenderWindow()->pollEvent(event)) {
        switch(event.type) {
        case sf::Event::Closed : m_window.finish(); break;
        case sf::Event::KeyPressed :
                if(event.key.code == sf::Keyboard::F5) m_window.toggleFullscreen(); break;
        }
        m_master.handleInput(event);
    }
}

void Game::update() {
    m_window.update();
   // m_button.update();
}

void Game::render() {
    m_window.beginDraw();
    m_master.draw();
    m_window.endDraw();
}
