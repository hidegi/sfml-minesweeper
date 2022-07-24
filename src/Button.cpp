#include "Button.h"
#include <iostream>

Button::Button(Context* p_context, float  p_x, float p_y, bool p_mine) :
    m_context(p_context),
    m_isFlagged(false),
    m_isCovered(true),
    m_position(p_x, p_y),
    m_mines(0),
    m_adjacentFlags(0),
    m_isMine(p_mine),
    m_isSelected(false)
{

    m_window = m_context->m_window;
    if(!m_context)
        std::cout << "NULL CONTEXT!!" << std::endl;
    if(!m_window)
        std::cout << "NULL WINDOW!!" << std::endl;
}

void Button::create() {
    m_sprite.setTexture(*(m_context->getTexture(Context::Type::Game)));
    changeTexture(State::Covered);

    m_sprite.setPosition(m_position);
    m_sprite.setScale(sf::Vector2f(2.f, 2.f));
}

void Button::clearAdjacents() {
    if(!m_adjacents.empty())
    m_adjacents.clear();
}

void Button::uncover () {
    if(m_isFlagged)
    return;

    if(m_isMine) {
        changeTexture(State::Mine);
    } else if(m_mines)
    changeTexture(m_digit);
    else
    changeTexture(State::Uncovered);
    m_isCovered = false;
}

void Button::boom(Button* p_caller) {
    for(auto a : m_adjacents) {
            if(!a->isCovered() || a == p_caller || a->isFlagged())
                continue;
                a->uncover();
           if(!a->getMines())
              a->boom(this);
    }
}

void Button::uncoverAdjacents() {
    for(auto a : m_adjacents)
        a->uncover();

}


void Button::handleEvent(const sf::Event& event) {
     if(sf::Mouse::isButtonPressed(sf::Mouse::Left)) {

     if(event.type == (sf::Event::MouseMoved)) {
        if(m_isCovered && !m_isFlagged)
           if(!onButton()) {
            changeTexture(State::Covered);
           } else {
            changeTexture(State::Uncovered);
           }
           return;
        }
        if(onButton()) {
        countAdjacentFlags();
        }

        if(onButton() && (!m_isMine && !m_isCovered) && m_adjacentFlags == m_mines) {
            boom(this);
        }

    }

    if(event.type == sf::Event::MouseButtonReleased) {

        if(onButton()) {
        if(event.mouseButton.button == sf::Mouse::Left) {
            if(m_isCovered && !m_isFlagged) {
               if(!m_mines && !m_isMine) {
                changeTexture(State::Uncovered);
                boom(this);
                }
                else
                    changeTexture(m_digit);
                m_isCovered = false;
            }
        } else if(event.mouseButton.button == sf::Mouse::Right) {
            if(!m_isCovered)
                return;
            if(m_isFlagged) {
                changeTexture(State::Covered);
            } else {
                changeTexture(State::Flagged);
            }
                     m_isFlagged = !m_isFlagged;
            }
        }
    }
}

bool Button::isMine() {
    return m_isMine;
}

void Button::countAdjacentFlags() {
    int count = 0;
    for(auto a : m_adjacents)
        if(a->isFlagged())
            ++count;
    m_adjacentFlags = count;
}

void Button::countMines() {

    for(auto it = m_adjacents.begin(); it != m_adjacents.end(); ++it) {
        if((*it)->isMine())
            ++m_mines;
    }
    m_digit = (Digit) (m_mines - 1);
}

bool Button::onButton() {
    sf::Vector2i pos = sf::Mouse::getPosition(*m_window->getRenderWindow());
    return m_sprite.getGlobalBounds().contains(pos.x, pos.y);
}

void Button::update() {

}

void Button::addAdjacent(Button* p_button) {
    m_adjacents.push_back(std::move(p_button));
}


void Button::draw(sf::RenderTarget& p_window, sf::RenderStates p_states) const{
    p_window.draw(m_sprite, p_states);
}

void Button::changeTexture(State type) {
    sf::IntRect textureRect((int)type * SIZE, 0, SIZE, SIZE);
    m_sprite.setTextureRect(textureRect);
     m_sprite.setScale(sf::Vector2f(2.f, 2.f));
    m_state = type;
}

void Button::changeTexture(Digit digit) {
    sf::IntRect textureRect((int)digit * SIZE, SIZE, SIZE, SIZE);
    m_sprite.setTextureRect(textureRect);
     m_sprite.setScale(sf::Vector2f(2.f, 2.f));
    m_state = State::Uncovered;
}
