#pragma once

#include <SFML/Window.hpp>
#include "InputComponent.h"

class InputSystem
{
public:
    void processEvent( const sf::Event& event )
    {
        if( event.type == sf::Event::KeyPressed )
            m_keyStates[event.key.code] = true;
        else if( event.type == sf::Event::KeyReleased )
            m_keyStates[event.key.code] = false;
    }

    bool isKeyPressed( sf::Keyboard::Key key ) const
    {
        auto it = m_keyStates.find( key );
        return it != m_keyStates.end() && it->second;
    }

    void clearKey(sf::Keyboard::Key key)
    {
        m_keyStates[key] = false;
    }

    void clearAllKeys()
    {
        m_keyStates.clear();
    }

private:
    std::unordered_map<sf::Keyboard::Key, bool> m_keyStates;
};