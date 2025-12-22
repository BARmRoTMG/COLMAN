#pragma once

#include <SFML/Graphics.hpp>
#include "EntityFactory.h"
#include "StateMachine.h"

class Game
{
public:
	Game();
	~Game();

public:
    void InitStates();
    void RunEvent(const std::string& event);
    void RunUpdate(float dt);

private:
    sf::RenderWindow        m_window;
    sf::Clock               m_clock;

public:
    EntityFactory           m_factory;
    StateMachine            m_stateMachine;
};
