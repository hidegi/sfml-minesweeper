#ifndef SHAREDCONTEXT_H_INCLUDED
#define SHAREDCONTEXT_H_INCLUDED
#include <unordered_map>
#include <SFML/Graphics.hpp>
#include <Window.h>
#include <iostream>

class Context {
    public:
    enum class Type{Game, Emoticon, Score};
    typedef std::unordered_map<Type, std::unique_ptr<sf::Texture>> Textures;

    Window*     m_window;
    Context(Window* window) : m_window(window) {
        std::cout << "called context.." << std::endl;
        if(m_window)
            std::cout << "window not NULL!!" << std::endl;
    }

    Textures    m_textures;
    void registerTexture(Type type, const std::string& path) {
        m_textures[type] = std::make_unique<sf::Texture>();
        m_textures[type].get()->loadFromFile(path);
        if(m_textures[type].get() == nullptr)
            std::cout << "null.." << std::endl;
        else
            std::cout << "not null.." << std::endl;
    }

    sf::Texture* getTexture(Type type) {return (m_textures[type].get());}
    private:

};

#endif // SHAREDCONTEXT_H_INCLUDED
