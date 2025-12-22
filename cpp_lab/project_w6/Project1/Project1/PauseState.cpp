#include "PauseState.h"
#include <iostream>

//------------------------------------------------------------------------------------------------//
PauseState::PauseState(sf::RenderWindow& rw, ResourceManager& rm, EntityFactory& ef, Callback resumeGame)
	: IState(rw, rm, ef), m_resume(resumeGame)
{
	InitEntities();
}
//------------------------------------------------------------------------------------------------//
void PauseState::InitEntities()
{
	auto st = m_factory.Create("text_pause", m_window);
	if (st)
		m_entities.push_back(st);
}
//------------------------------------------------------------------------------------------------//
void PauseState::handleEvent(const sf::Event& e)
{
	if (e.type == sf::Event::KeyPressed &&
		(e.key.code == sf::Keyboard::Space || e.key.code == sf::Keyboard::Escape))
	{
		std::cout << "Game resumed..." << std::endl;
		if (m_resume)
			m_resume();
	}
}
//------------------------------------------------------------------------------------------------//
void PauseState::update(float dt)
{

}
//------------------------------------------------------------------------------------------------//
void PauseState::render()
{
	sf::RectangleShape overlay(sf::Vector2f(m_window.getSize()));
	overlay.setFillColor(sf::Color(128, 128, 128, 2));
	m_window.draw(overlay);

	m_renderSystem.render(m_window, m_entities);
	m_window.display();
}
//------------------------------------------------------------------------------------------------//