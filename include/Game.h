#ifndef GAME_H
#define GAME_H
#include <SFML/Graphics.hpp>
#include <Window.h>
#include <Button.h>
#include <SharedContext.h>
#include <Master.h>
class Game
{
    public:
                            Game();
                           ~Game();

        void                handleInput();
        void                update();
        void                render();

        Window*             getWindow();
        sf::Time            getElapsed();
        void                restart();
        void                run();
    private:

        sf::Clock           m_clock;
        float               m_elapsed;
        Window              m_window;
        Context             m_context;
        //Button              m_button;
        //Button              m_button2;
        Master              m_master;

};

#endif // GAME_H
