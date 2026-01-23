#pragma once
#include "World.h"

class TrafficLightSystem
{
public:
	void Update(float dt, World& world)
	{
		auto controllers = world.View<TrafficLightController>();

		if (controllers.empty())
			return;

		auto& ctrl = world.GetComponent<TrafficLightController>(controllers[0]);

		ctrl.timer += dt;

		if (ctrl.timer >= 5.0f)
		{
			ctrl.timer -= 5.0f;

			int currentDir = static_cast<int>(ctrl.current);
			currentDir = (currentDir + 1) % static_cast<int>(Direction::Total);
			ctrl.current = static_cast<Direction>(currentDir);
		}

		auto lights = world.View<TrafficLight>();

		for (auto lightEntity : lights)
		{
			auto& light = world.GetComponent<TrafficLight>(lightEntity);

			light.green = (light.lane == ctrl.current);
		}
	}
};