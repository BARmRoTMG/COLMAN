#include "Game.h"
#include "MenuState.h"
#include "PlayState.h"
#include "PauseState.h"

//------------------------------------------------------------------------------------------------//
Game::Game() : m_window( sf::VideoMode(800, 600 ), "Advanced Lab Project")
{
}
//------------------------------------------------------------------------------------------------//
Game::~Game()
{
    
}
//------------------------------------------------------------------------------------------------//
void Game::InitStates()
{
    m_stateMachine.registerState<MenuState>("menu", m_factory,
        [this]()
        {
            m_stateMachine.changeState("play");
        });

    m_stateMachine.registerState<PlayState>("play", m_factory,
        [this]() { m_stateMachine.changeState("pause"); }, // Pause Callback
        [this]() { m_stateMachine.changeState("menu"); }   // Exit Callback
    );

    m_stateMachine.registerState<PauseState>("pause", m_factory,
        [this]() { m_stateMachine.changeState("play"); } // Resume (pop back to play)
    );
    
    m_stateMachine.changeState("menu");
}
//------------------------------------------------------------------------------------------------//
void Game::RunEvent( const std::string& event )
{
    if (auto state = m_stateMachine.currentState())
    {
        state->handleEvent(event);
    }
}
//------------------------------------------------------------------------------------------------//
void Game::RunUpdate( float dt )
{
    if (auto state = m_stateMachine.currentState())
    {
        state->update(dt);
    }
}
//------------------------------------------------------------------------------------------------//