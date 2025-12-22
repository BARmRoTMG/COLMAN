#pragma once
#include "Entity.h"
#include "ResourceManager.h"

class EntityFactory
{
public:
    EntityFactory( ResourceManager& rm );

    Entity* Create( const std::string& type, sf::RenderWindow& wnd );

private:
    ResourceManager& m_rm;
};