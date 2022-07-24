#include "Window.h"
#include <iostream>
Window::Window()
{
     std::cout << "here window.." << std::endl;
    init("Window",  sf::Vector2u(640, 480));
}

Window::Window(const std::string& title, const sf::Vector2u& size) {

    init(title, size);
    std::cout << "created window.." << std::endl;
}

Window::~Window() {
    destroy();
}

sf::RenderWindow* Window::getRenderWindow() {
    return &m_window;
}

void Window::init(const std::string& title, const sf::Vector2u& size) {
    m_windowTitle = title;
    m_windowSize = size;
    m_isFullscreen = false;
    m_isDone = false;
    m_window.setFramerateLimit(60);
    create();
}

void Window::create() {
    unsigned int style = (sf::Style::Close | sf::Style::Titlebar);

    m_window.create({m_windowSize.x, m_windowSize.y, 32}, m_windowTitle, style);
}

void Window::destroy() {
    m_window.close();
}

void Window::beginDraw() {m_window.clear(sf::Color::Black);}
void Window::endDraw() {m_window.display();}

bool Window::isDone() {return m_isDone;}
bool Window::isFullscreen() {return m_isFullscreen;}

void Window::draw(sf::Drawable& drawable) {
    m_window.draw(drawable);
}

sf::Vector2u Window::getWindowSize() {return m_windowSize;}

void Window::toggleFullscreen() {
    m_isFullscreen = !m_isFullscreen;
    destroy();
    create();
}

void Window::update() {

}
