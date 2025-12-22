#include "PlayState.h"

//------------------------------------------------------------------------------------------------//
PlayState::PlayState( sf::RenderWindow& rw, ResourceManager& rm, EntityFactory& ef, Callback pauseGame )
	: IState( rw, rm, ef ), m_pause( pauseGame )
{
    InitEntities();
}
//------------------------------------------------------------------------------------------------//
void PlayState::InitEntities()
{
    auto p = m_factory.Create( "player", m_window );
    if( p )
        m_entities.push_back( p );

    auto ec = m_factory.Create( "enemy_chase", m_window );
    if( ec )
        m_entities.push_back( ec );

    auto er = m_factory.Create( "enemy_random", m_window );
    if( er )
        m_entities.push_back( er );

    auto i = m_factory.Create( "enemy_idle", m_window );
    if( i )
        m_entities.push_back( i );

    auto lr = m_factory.Create( "enemy_leftright", m_window );
    if( lr )
        m_entities.push_back( lr );
}
//------------------------------------------------------------------------------------------------//
void PlayState::handleEvent( const sf::Event& e )
{
    m_inputSystem.processEvent( e );
}
//------------------------------------------------------------------------------------------------//
void PlayState::update( float dt )
{
    m_playerControl.update( m_inputSystem, m_entities );
    m_aiSystem.update( m_entities, dt, m_window.getSize() );
    m_movementSystem.update( m_entities, dt );
    m_boundarySystem.update( m_window, m_entities );
    m_behaviorVisualizerSystem.update( m_entities );
}
//------------------------------------------------------------------------------------------------//
void PlayState::render()
{
	m_window.clear( sf::Color::Black );
	m_renderSystem.render( m_window, m_entities );
	m_window.display();
}
//------------------------------------------------------------------------------------------------//