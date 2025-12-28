#pragma once
#include "World.h"

class TrafficLightSystem
{
public:
	void Update( float dt, World& world )
	{
		
	}

private:
	Direction next( Direction curr )
	{
		return Direction::North;
	}

	void applyToLights( World& world, Direction current )
	{
		
	}
};