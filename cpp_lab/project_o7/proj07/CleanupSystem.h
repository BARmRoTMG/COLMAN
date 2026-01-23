#pragma once
#include "World.h"
#include <vector>

class CleanupSystem
{
public:
	void Update(World& world)
	{
		const float SCREEN_WIDTH = 800.0f;
		const float SCREEN_HEIGHT = 800.0f;

		auto entities = world.View<Position>();

		std::vector<Entity> toDelete;

		for (auto entity : entities)
		{
			const auto& pos = world.GetComponent<Position>(entity);

			if (pos.x < 0.0f || pos.x > SCREEN_WIDTH ||
				pos.y < 0.0f || pos.y > SCREEN_HEIGHT)
			{
				toDelete.push_back(entity);
			}
		}
		for (auto entity : toDelete)
		{
			world.DestroyEntity(entity);
		}
	}
};