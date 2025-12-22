#pragma once

#include "Entity.h"

struct IAiBehavior
{
	virtual ~IAiBehavior() = default;
	virtual void update(const std::vector<Entity*>& entities, Entity& self, float dt, int screenX, int screenY) = 0;
};