#pragma once
#include "IState.h"

class PauseState : public IState
{
public:
    PauseState( sf::RenderWindow& rw, ResourceManager& rm, EntityFactory& ef );

public:
    virtual void InitEntities() override;
    virtual void handleEvent( const sf::Event& e ) override;
    virtual void update( float dt ) override;
    virtual void render() override;
};
