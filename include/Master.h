#ifndef MASTER_H
#define MASTER_H
#define SIZE 32
#include <map>
#include <Button.h>
#include <SharedContext.h>

// 81  -> 10
// 256 -> 40
// 480 -> 99

class Master
{
    public:
        typedef const unsigned int Counter;
        typedef std::map<Counter, std::unique_ptr<Button>> Board;

        enum class Difficulty {Beginner = 10, Intermediate = 40, Expert = 99, Evil = 130};

                        Master(Context* p_context, Difficulty p_difficulty);
                       ~Master();
        void            build();
        void            draw();
        void            handleInput(const sf::Event& p_event);
        void            linkAdjacents();
        void            scatterMines();

    private:
        bool            m_gameOver;
        int             m_uncovered;
        int             m_width;
        int             m_height;
        int             m_max;
        bool            m_built;
        unsigned int    m_mines;
        Board           m_board;
        Context*        m_context;
        Window*         m_window;
        Difficulty      m_difficulty;
        sf::Time        m_time;
        sf::Clock       m_clock;
};

#endif // MASTER_H
