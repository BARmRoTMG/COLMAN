#include "Game.h"
#include "MenuState.h"
#include "PlayState.h"
#include "PauseState.h"

//------------------------------------------------------------------------------------------------//
Game::Game()
    : m_window( sf::VideoMode( 800, 600 ), "Week 5 - Strategy & Factory" ),
    m_factory( m_resourceManager )
{
}
//------------------------------------------------------------------------------------------------//
Game::~Game()
{
    
}
//------------------------------------------------------------------------------------------------//
void Game::InitStates()
{
    m_stateMachine.registerState<MenuState>( "menu", m_window, m_resourceManager, m_factory,
        [this]()
        {
            m_stateMachine.changeState( "play" );
        } );

    m_stateMachine.registerState<PlayState>( "play", m_window, m_resourceManager, m_factory,
        [this]()
        {
            m_stateMachine.changeState( "pause" );
        } );
    m_stateMachine.registerState<PauseState>("pause", m_window, m_resourceManager, m_factory,
        [this]()
        {
            m_stateMachine.changeState("play");
        });

    
    m_stateMachine.changeState( "menu" );
}
//------------------------------------------------------------------------------------------------//
void Game::Run()
{
    float dt;
    sf::Event event;

    while( m_window.isOpen() )
    {
        dt = m_clock.restart().asSeconds();
        
        while( m_window.pollEvent( event ) )
        {
            if( event.type == sf::Event::Closed )
                m_window.close();

            m_stateMachine.currentState()->handleEvent( event );
        }

        m_stateMachine.currentState()->update( dt );

        m_stateMachine.currentState()->render();
    }
}
//------------------------------------------------------------------------------------------------//