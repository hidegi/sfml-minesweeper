#pragma once
#include <SFML/Graphics.hpp>
class Window
{
    public:
                                Window();
                                Window(const std::string& title, const sf::Vector2u& size);
                               ~Window();

        void                    beginDraw();
        void                    endDraw();

        void                    update();
        bool                    isDone();
        bool                    isFullscreen();
        void                    toggleFullscreen();

        sf::RenderWindow*       getRenderWindow();
        sf::Vector2u            getWindowSize();

        void                    draw(sf::Drawable& drawable);
        void                    finish() {m_isDone = true;}
    private:

        void                    init(const std::string& title, const sf::Vector2u& size);
        void                    create();
        void                    destroy();

        sf::RenderWindow        m_window;
        sf::Vector2u            m_windowSize;
        std::string             m_windowTitle;
        bool                    m_isDone;
        bool                    m_isFullscreen;
};
