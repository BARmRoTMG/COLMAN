#include "PlayState.h"
#include <iostream>

//------------------------------------------------------------------------------------------------//
PlayState::PlayState( EntityFactory& ef, Callback pauseGame, Callback exitGame )
	: IState( ef ), m_pause(pauseGame), m_exit(exitGame)
{
	InitEntities();
}
//------------------------------------------------------------------------------------------------//
void PlayState::InitEntities()
{
	auto p = m_factory.Create("player");
	if (p)
		m_entities.push_back(p);

	auto ea = m_factory.Create("enemy_avoid");
	if (ea)
		m_entities.push_back(ea);

	auto ud = m_factory.Create("enemy_upDown");
	if (ud)
		m_entities.push_back(ud);
}
//------------------------------------------------------------------------------------------------//
void PlayState::handleEvent( const std::string& event )
{
    // 1. Pause Event (Space)
    if (event == "Space")
    {
        if (m_pause)
            m_pause();
    }
    // 2. Escape Event (Escape) -> Reset Game and go to Menu
    else if (event == "Escape")
    {
        clear();          // Delete current entities
        InitEntities();   // Re-create them at starting positions (Reset)

        if (m_exit)
            m_exit();
    }
}
//------------------------------------------------------------------------------------------------//
void PlayState::update( float dt )
{
    m_movementSystem.update(m_entities, dt);
    m_boundarySystem.update(800, 600, m_entities);
    m_aiSystem.update(m_entities, dt, 800, 600);
}
//------------------------------------------------------------------------------------------------//
void PlayState::clear()
{
    for (auto* e : m_entities)
    {
        delete e;
    }
    m_entities.clear();
}
//------------------------------------------------------------------------------------------------//