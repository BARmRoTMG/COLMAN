#pragma once
#include "World.h"

class MovementSystem
{
public:
	void Update(float dt, World& world)
	{
		auto entities = world.View<Position, Velocity>();

		for (auto entity : entities)
		{
			auto& pos = world.GetComponent<Position>(entity);
			auto& vel = world.GetComponent<Velocity>(entity);

			pos.x += vel.valueX * dt;
			pos.y += vel.valueY * dt;
		}
	}
};