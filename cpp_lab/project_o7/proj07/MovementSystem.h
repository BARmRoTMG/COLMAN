#pragma once
#include "World.h"

class MovementSystem
{
public:
	void Update( float dt, World& world )
	{
		for (Entity e : world.View<Position, Velocity>())
		{
			auto& p = world.GetComponent<Position>(e);
			auto& v = world.GetComponent<Velocity>(e);

			p.x += dt * v.valueX;
			p.y += dt * v.valueY;
		}
		
	}
};