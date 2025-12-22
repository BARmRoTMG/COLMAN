#pragma once
#include "IState.h"
#include "MovementSystem.h"
#include "InputSystem.h"
#include "PlayerControlSystem.h"
#include "BoundarySystem.h"
#include "AISystem.h"
#include "BehaviorVisualizerSystem.h"

class PlayState : public IState
{
public:
    PlayState( sf::RenderWindow& rw, ResourceManager& rm, EntityFactory& ef, Callback pauseGame );

public:
    virtual void InitEntities() override;
    virtual void handleEvent( const sf::Event& e ) override;
    virtual void update( float dt ) override;
    virtual void render() override;

private:
    Callback m_pause;

private:
    MovementSystem          m_movementSystem;
    InputSystem             m_inputSystem;
    PlayerControlSystem     m_playerControl;
    BoundarySystem          m_boundarySystem;
    AISystem                m_aiSystem;
    BehaviorVisualizerSystem m_behaviorVisualizerSystem;
};
