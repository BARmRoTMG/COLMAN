#pragma once
#include "IState.h"
#include "MovementSystem.h"
#include "BoundarySystem.h"
#include "AISystem.h"

class PlayState : public IState
{
public:
    PlayState( EntityFactory& ef, Callback pauseGame, Callback exitGame );

public:
    virtual void InitEntities() override;
    virtual void handleEvent( const std::string& event ) override;
    virtual void update( float dt ) override;

private:
    void clear();

private:
    Callback m_pause;
    Callback m_exit;

public:
    MovementSystem          m_movementSystem;
    BoundarySystem          m_boundarySystem;
    AISystem                m_aiSystem;
};
