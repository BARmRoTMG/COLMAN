#pragma once
#include "TrafficLightSystem.h"
#include "MovementSystem.h"
#include "InteractionSystem.h"
#include "CleanupSystem.h"

class Simulator
{
public:
    Simulator();
	~Simulator();

public:
    void Update( float dt );
    World& GetData() { return m_world; }

private:
    World               m_world;

private:
    TrafficLightSystem  m_trafficSystem;
    MovementSystem      m_movementSystem;
    InteractionSystem   m_interactionSystem;
    CleanupSystem       m_cleanupSystem;
};
