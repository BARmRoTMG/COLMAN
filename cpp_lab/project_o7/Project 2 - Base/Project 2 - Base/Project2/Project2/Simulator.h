#pragma once
#include "World.h"
#include "TrafficLightSystem.h"
#include "MovementSystem.h"
#include "InteractionSystem.h"
#include "CleanupSystem.h"
#include "RenderSystem.h"

class Simulator
{
public:
    Simulator();
	~Simulator();

public:
	void Run();

private:
    void handleEvents();
    void update( float dt );
    void render();

private:
    sf::RenderWindow    m_window;
    World               m_world;

private:
    TrafficLightSystem  m_trafficSystem;
    MovementSystem      m_movementSystem;
    InteractionSystem   m_interactionSystem;
    CleanupSystem       m_cleanupSystem;
    RenderSystem        m_renderSystem;
};
