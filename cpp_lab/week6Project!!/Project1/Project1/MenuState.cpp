#include "MenuState.h"

//------------------------------------------------------------------------------------------------//
MenuState::MenuState(EntityFactory& ef, Callback startGame)
	: IState(ef), m_start(startGame)
{
	InitEntities();
}
//------------------------------------------------------------------------------------------------//
void MenuState::InitEntities()
{
}
//------------------------------------------------------------------------------------------------//
void MenuState::handleEvent(const std::string& e)
{
	if (e == "enter")
	{
		if (m_start) m_start();
	}
}
//------------------------------------------------------------------------------------------------//
void MenuState::update(float dt)
{
	//if (sf::Keyboard::isKeyPressed(sf::Keyboard::Enter))
	//{
	//	if (m_start) m_start();
	//}
}
//------------------------------------------------------------------------------------------------//