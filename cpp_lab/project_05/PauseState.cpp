#include "PauseState.h"
#include <iostream>

//------------------------------------------------------------------------------------------------//
PauseState::PauseState( EntityFactory& ef, Callback resumeGame )
    : IState( ef ), m_resume(resumeGame)
{
    InitEntities();
}
//------------------------------------------------------------------------------------------------//
void PauseState::InitEntities()
{
    
}
//------------------------------------------------------------------------------------------------//
void PauseState::handleEvent( const std::string& event )
{
    if (event == "Space")
    {
        if (m_resume)
            m_resume();
    }
}
//------------------------------------------------------------------------------------------------//
void PauseState::update( float dt )
{
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
    {
        if (m_resume)
            m_resume();
    }
}
//------------------------------------------------------------------------------------------------//