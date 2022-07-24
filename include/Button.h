#ifndef BUTTON_H
#define BUTTON_H
#define SIZE 16
#include <Window.h>
#include <SFML/Graphics.hpp>
#include <SFML/Window/Event.hpp>
#include <SFML/Graphics/RenderStates.hpp>
#include <SFML/Graphics/RenderTarget.hpp>
#include <SharedContext.h>

class Button : public sf::Drawable, public sf::Transformable
{
    public:
                                    Button(Context* p_context, float, float, bool);
                                   ~Button() {
                                        while(!m_adjacents.empty())
                                            m_adjacents.pop_back();
                                        }
                                    enum Type  {Corner, Edge, Center};
                                    enum State {Covered = 0, Uncovered = 1, Flagged = 2, Mine = 5, Mine_Selected = 6, Not_Mine = 7};
                                    enum Digit {One = 0, Two, Three, Four, Five, Six, Seven, Eight};

        void                        uncover();
        void                        uncoverAdjacents();
        void                        flagging();
        void                        clearAdjacents();
        void                        setContext(Context* p_context) {m_context = p_context;}
        void                        update();
        void                        handleEvent(const sf::Event& event);
        void                        draw(sf::RenderTarget& target, sf::RenderStates states) const;
        void                        changeTexture(State state);
        void                        changeTexture(Digit digit);
        void                        create();
        void                        addAdjacent(Button* p_button);
        void                        countMines();
        void                        setSelected(bool p_selected) {m_isSelected = p_selected;}

        bool                        isCovered() {return m_isCovered;}
        bool                        isFlagged() {return m_isFlagged;}
        bool                        isMine();
        void                        setMine(bool p_mine) {m_isMine = p_mine;}
        void                        countAdjacentFlags();
        void                        boom(Button* p_caller);
        void                        setCovered(bool p_covered) {m_isCovered = p_covered;}
        int                         getMines() {return m_mines;}
        bool                        onButton();
    private:


        bool                        m_isFlagged;
        bool                        m_isCovered;
        bool                        m_isMine;
        bool                        m_isSelected;

        State                       m_state;
        Digit                       m_digit;
        unsigned int                m_adjacentFlags;
        unsigned int                m_mines;
        sf::Sprite                  m_sprite;
        sf::Texture                 m_texture;
        Window*                     m_window;
        Context*                    m_context;
        sf::Vector2f                m_position;
        std::vector<Button*>        m_adjacents;
};

#endif // BUTTON_H
