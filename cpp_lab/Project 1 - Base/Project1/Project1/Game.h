#pragma once

#include <SFML/Graphics.hpp>
#include "ResourceManager.h"
#include "EntityFactory.h"
#include "MovementSystem.h"
#include "RenderSystem.h"
#include "InputSystem.h"
#include "PlayerControlSystem.h"
#include "BoundarySystem.h"
#include "PauseSystem.h"
#include "AISystem.h"

class Game
{
public:
	Game();
	~Game();

public:
    void InitEntities();
	void Run();

private:
    void processEvents();
    void update( float dt );
    void render();

private:
    sf::RenderWindow        m_window;
    sf::Clock               m_clock;
    sf::Color               m_background;
    bool                    m_isPaused;

private:
    ResourceManager         m_resourceManager;
    EntityFactory           m_factory;
    std::vector<Entity*>    m_entities;

private:
    MovementSystem          m_movementSystem;
    RenderSystem            m_renderSystem;
    InputSystem             m_inputSystem;
    PlayerControlSystem     m_playerControl;
    BoundarySystem          m_boundarySystem;
    PauseSystem             m_pauseSystem;
    AISystem                m_aiSystem;
};
