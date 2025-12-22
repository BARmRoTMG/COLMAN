#include "Game.h"

//------------------------------------------------------------------------------------------------//
Game::Game()
    : m_window( sf::VideoMode( 800, 600 ), "Week 5 - Strategy & Factory" ),
    m_background( sf::Color::Black ),
    m_isPaused( false ),
    m_factory( m_resourceManager )
{
}
//------------------------------------------------------------------------------------------------//
Game::~Game()
{
    for( auto p : m_entities )
        delete p;
}
//------------------------------------------------------------------------------------------------//
void Game::InitEntities()
{
    auto p = m_factory.Create( "player", m_window );
    if( p )
        m_entities.push_back( p );

    auto ec = m_factory.Create( "enemy_chase", m_window );
    if( ec )
        m_entities.push_back( ec );

    //auto er = m_factory.Create( "enemy_random", m_window );
    //if( er )
    //    m_entities.push_back( er );

    auto pt = m_factory.Create( "text_pause", m_window );
    if( pt )
        m_entities.push_back( pt );
}
//------------------------------------------------------------------------------------------------//
void Game::Run()
{
    float dt;
    while( m_window.isOpen() )
    {
        dt = m_clock.restart().asSeconds();
        processEvents();
        update( dt );
        render();
    }
}
//------------------------------------------------------------------------------------------------//
void Game::processEvents()
{
    sf::Event event;
    while( m_window.pollEvent( event ) )
    {
        if( event.type == sf::Event::Closed )
            m_window.close();

        if( event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Space )
            m_isPaused = !m_isPaused;

        m_inputSystem.processEvent( event );
    }
}
//------------------------------------------------------------------------------------------------//
void Game::update( float dt )
{
    m_pauseSystem.update( m_entities, m_isPaused );

    if( m_isPaused )
        return;

    m_playerControl.update( m_inputSystem, m_entities );
    m_aiSystem.update( m_entities, dt );
    m_movementSystem.update( m_entities, dt );
    m_boundarySystem.update( m_window, m_entities );
}
//------------------------------------------------------------------------------------------------//
void Game::render()
{
    m_window.clear( m_background );
    m_renderSystem.render( m_window, m_entities );
    m_window.display();
}
//------------------------------------------------------------------------------------------------//