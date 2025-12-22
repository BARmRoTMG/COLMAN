#include "MenuState.h"

//------------------------------------------------------------------------------------------------//
MenuState::MenuState( sf::RenderWindow& rw, ResourceManager& rm, EntityFactory& ef, Callback startGame )
	: IState( rw, rm, ef ), m_start( startGame )
{
	InitEntities();
}
//------------------------------------------------------------------------------------------------//
void MenuState::InitEntities()
{
	auto st = m_factory.Create( "text_start", m_window );
	if( st )
		m_entities.push_back( st );
}
//------------------------------------------------------------------------------------------------//
void MenuState::handleEvent( const sf::Event& e )
{
	if( e.type == sf::Event::KeyPressed && e.key.code == sf::Keyboard::Enter )
		m_start();
}
//------------------------------------------------------------------------------------------------//
void MenuState::update( float dt )
{
	
}
//------------------------------------------------------------------------------------------------//
void MenuState::render()
{
	m_window.clear( sf::Color::Red );
	m_renderSystem.render( m_window, m_entities );
	m_window.display();
}
//------------------------------------------------------------------------------------------------//