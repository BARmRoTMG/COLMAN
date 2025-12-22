#pragma once

#include "Entity.h"

struct IAiBehavior
{
	virtual ~IAiBehavior() = default;
	virtual void update( const std::vector<Entity*>& entities, Entity& self, float dt, sf::Vector2u screenSize ) = 0;
};
