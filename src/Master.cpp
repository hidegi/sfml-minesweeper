#include "Master.h"

Master::Master(Context* p_context, Difficulty p_difficulty) :
    m_context(p_context),
    m_difficulty(p_difficulty),
    m_mines(0),
    m_gameOver(false),
    m_built(false),
    m_uncovered(0),
    m_time(sf::Time::Zero)
{
    switch(m_difficulty) {
    case Difficulty::Beginner:
        m_width = m_height = 9; break;
    case Difficulty::Intermediate:
        m_width = m_height = 16; break;
    case Difficulty::Expert:
        m_width = 30; m_height = 16; break;
    }

    m_max = m_width * m_height;
    m_window = m_context->m_window;
    if(!m_context)
        std::cout << "master: null Context!!" << std::endl;
    if(!m_window)
        std::cout << "master: null Window!!" << std::endl;

    std::cout << "created master.." << std::endl;
}
Master::~Master() {}

void Master::build() {
    int count = 1;
    int realMines = 0;
    m_mines = 0;
    if(!m_board.empty())
    m_board.clear();

    for(size_t i = 0; i < m_height; ++i) {
        for(size_t j = 0; j < m_width; ++j, ++count) {
        m_board.emplace(count,std::move(std::make_unique<Button>(m_context, j * SIZE * 2.f, i * SIZE * 2.f, false)));
        m_board.at(count)->create();
        }
    }

    scatterMines();

}



void Master::scatterMines() {

    int index;
    int realMines = 0;

  /*  bool clicked = false;
    while(!clicked) {

    if(event.type == sf::Event::MouseButtonReleased && event.mouseButton.button == sf::Mouse::Left) {
           clicked = true;}

        std::cout << "click a button.." << std::endl;
    /*for( auto it = m_board.begin(); it != m_board.end(); ++it) {


    }
    }*/
    std::cout << "thank!!" << std::endl;
    while(m_mines < (int)m_difficulty) {
        index = 1 + (std::rand() % (m_board.size()));
        if(m_board[index]->isMine())
            index = 1 + (std::rand() % (m_board.size()));

        m_board[index]->setMine(true);
        ++realMines;
        ++m_mines;
    }

  /*  auto it = std::find_if(m_board.begin(), m_board.end(),
                          [](auto &b)->bool {
                           return b.second->onButton();});
    it->second->setMine(false);*/
    std::cout << "actual mines: " << realMines << std::endl;
    linkAdjacents();
    m_clock.restart();
}

void Master::draw() {

    for( auto it = m_board.begin(); it != m_board.end(); ++it)
        m_window->draw(*it->second);
}

void Master::handleInput(const sf::Event& p_event) {

    if(m_gameOver) {
            if(sf::Mouse::isButtonPressed(sf::Mouse::Middle) ||
            ((p_event.type == sf::Event::KeyPressed) && (p_event.key.code == sf::Keyboard::Space))) {
                    m_gameOver =  false;
                    build();
            }

    } else {
                int uncovered = 0;
    for( auto it = m_board.begin(); it != m_board.end(); ++it) {
        it->second->handleEvent(p_event);

        if(!it->second->isCovered()) {
        if(it->second->isMine()) {
        it->second->changeTexture(Button::State::Mine_Selected);
            for(auto it2 = m_board.begin(); it2 != m_board.end(); ++it2) {
                if(it2 != it)
                if(it2->second->isMine() && !it2->second->isFlagged()) {
                    it2->second->changeTexture(Button::State::Mine);
                    it2->second->uncover();

                } else if(it2->second->isFlagged() && !it2->second->isMine()) {
                    it2->second->changeTexture(Button::State::Not_Mine);
                    it2->second->uncover();
                }
            }

            std::cout << "GAME OVER!! time taken: " << m_clock.getElapsedTime().asSeconds() << " s.. (Press SPACE to restart..)" << std::endl;
            m_gameOver = true;
            break;
        } else {
             ++uncovered;

                }
            }

        }


           if(uncovered == m_max - (int)m_difficulty) {
                std::cout << "YOU WIN!! time taken: " << m_clock.getElapsedTime().asSeconds() << " s.. (Press SPACE to restart..)" << std::endl;

                    for( auto it = m_board.begin(); it != m_board.end(); ++it)
                        if(!it->second->isMine())
                            it->second->uncover();

                m_gameOver = true;

            }

    }

}

void Master::linkAdjacents() {
    unsigned int w = m_width;
    unsigned int h = m_height;
    unsigned int corner = 0;
    unsigned int edge = 0;
    unsigned int center = 0;
    for(size_t x = 1; x <= m_max; ++x) {

        m_board[x].get()->clearAdjacents();
        if(1 % x == 0) {
            //top left
           //  std::cout << "top left corner: " << x << std::endl;
            m_board[x].get()->addAdjacent(m_board[x + 1].get());
            m_board[x].get()->addAdjacent(m_board[x + w].get());
            m_board[x].get()->addAdjacent(m_board[x + w + 1].get());
            ++corner;
        }
        else if(x == w) {
            //top right
           //  std::cout << "top right corner: " << x << std::endl;
            m_board[x].get()->addAdjacent(m_board[x - 1].get());
            m_board[x].get()->addAdjacent(m_board[x + w - 1].get());
            m_board[x].get()->addAdjacent(m_board[x + w].get());
            ++corner;
        }

        else if(x % ((w * h) - w + 1) == 0){
            //bottom left
            // std::cout << "bottom left corner: " << x << std::endl;
            m_board[x].get()->addAdjacent(m_board[x + 1].get());
            m_board[x].get()->addAdjacent(m_board[x - w].get());
            m_board[x].get()->addAdjacent(m_board[x - w + 1].get());
            ++corner;
        }
        else if(x == m_max) {
            //bottom right
             //std::cout << "top right corner: " << x << std::endl;
            m_board[x].get()->addAdjacent(m_board[x - 1].get());
            m_board[x].get()->addAdjacent(m_board[x - w - 1].get());
            m_board[x].get()->addAdjacent(m_board[x - w].get());
            ++corner;
        }
        else if(x > 1 && x < w) {
            //top edge
            //std::cout << "top edge: " << x << std::endl;
            m_board[x].get()->addAdjacent(m_board[x - 1].get());
            m_board[x].get()->addAdjacent(m_board[x + 1].get());
            m_board[x].get()->addAdjacent(m_board[x + w - 1].get());
            m_board[x].get()->addAdjacent(m_board[x + w].get());
            m_board[x].get()->addAdjacent(m_board[x + w + 1].get());
            ++edge;
        }
        else if(x > ((w * h) - w + 1) && x < (w * h)) {
            //bottom edge
               //std::cout << "bottom edge: " << x << std::endl;
            m_board[x].get()->addAdjacent(m_board[x - 1].get());
            m_board[x].get()->addAdjacent(m_board[x + 1].get());
            m_board[x].get()->addAdjacent(m_board[x - w - 1].get());
            m_board[x].get()->addAdjacent(m_board[x - w].get());
            m_board[x].get()->addAdjacent(m_board[x - w + 1].get());
             ++edge;
        }
        else if(x % w == 0 && (x != w && x != w * h)) {
            //right edge
              // std::cout << "right edge: " << x << std::endl;
            m_board[x].get()->addAdjacent(m_board[x - 1].get());
            m_board[x].get()->addAdjacent(m_board[x - w].get());
            m_board[x].get()->addAdjacent(m_board[x - w - 1].get());
            m_board[x].get()->addAdjacent(m_board[x + w - 1].get());
            m_board[x].get()->addAdjacent(m_board[x + w].get());
             ++edge;
        }
        else if((x - 1) % w == 0 && (x != 1 && x != ((w * h) - w + 1))) {
            //left edge
             //  std::cout << "left edge: " << x << std::endl;
            m_board[x].get()->addAdjacent(m_board[x + 1].get());
            m_board[x].get()->addAdjacent(m_board[x - w].get());
            m_board[x].get()->addAdjacent(m_board[x - w + 1].get());
            m_board[x].get()->addAdjacent(m_board[x + w].get());
            m_board[x].get()->addAdjacent(m_board[x + w + 1].get());
             ++edge;
        } else {
            //default
             //std::cout << "default center: " << x << std::endl;
            m_board[x].get()->addAdjacent(m_board[x + 1].get());
            m_board[x].get()->addAdjacent(m_board[x - 1].get());
            m_board[x].get()->addAdjacent(m_board[x - w - 1].get());
            m_board[x].get()->addAdjacent(m_board[x - w].get());
            m_board[x].get()->addAdjacent(m_board[x - w + 1].get());
            m_board[x].get()->addAdjacent(m_board[x + w - 1].get());
            m_board[x].get()->addAdjacent(m_board[x + w].get());
            m_board[x].get()->addAdjacent(m_board[x + w + 1].get());
            ++center;
        }

        m_board[x].get()->countMines();
    }

      std::cout << "corners: " << corner << "\nedges: " << edge << "\ncenters: " << center << std::endl;
}


