#pragma once
#include <vector>
#include "Entity.h"
#include "PositionComponent.h"
#include "VelocityComponent.h"

class MovementSystem
{
public:
	void update(std::vector<Entity*>& entities)
	{
		for (auto e : entities)
		{
			auto pos = e->getComponent<PositionComponent>();
			auto vel = e->getComponent<VelocityComponent>();

			if (pos && vel)
			{
				pos->m_x += vel->m_vx;
				pos->m_y += vel->m_vy;
			}
		}
	}
};
