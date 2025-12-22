#pragma once

#include "IState.h"

class MenuState : public IState
{
public:
    MenuState( sf::RenderWindow& rw, ResourceManager& rm, EntityFactory& ef, Callback startGame );

public:
    virtual void InitEntities() override;
    virtual void handleEvent( const sf::Event& e ) override;
    virtual void update( float dt ) override;
    virtual void render() override;

private:
    Callback m_start;
};
