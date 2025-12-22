#pragma once

#include <SFML/Graphics.hpp>
#include "ResourceManager.h"
#include "EntityFactory.h"
#include "StateMachine.h"

class Game
{
public:
	Game();
	~Game();

public:
    void InitStates();
	void Run();

private:
    sf::RenderWindow        m_window;
    sf::Clock               m_clock;

private:
    ResourceManager         m_resourceManager;
    EntityFactory           m_factory;
    StateMachine            m_stateMachine;
};
