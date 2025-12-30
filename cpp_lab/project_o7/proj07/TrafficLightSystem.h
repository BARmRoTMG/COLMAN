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

        Entity controllerEntity = controllers[0];
        auto& controller = world.GetComponent<TrafficLightController>(controllerEntity);

        controller.timer += dt;

        if (controller.timer >= 5.0f)
        {
            controller.current = next(controller.current);
            controller.timer = 0.0f;

            auto trafficLights = world.View<TrafficLight>();

            for (Entity e : trafficLights)
            {
                auto& light = world.GetComponent<TrafficLight>(e);
                light.green = (light.lane == controller.current);
            }
        }
    }

private:
    Direction next(Direction current)
    {
        if (current == Direction::North)
        {
            return Direction::East;
        }
        else if (current == Direction::East)
        {
            return Direction::South;
        }
        else if (current == Direction::South)
        {
            return Direction::West;
        }
        else // Direction::West
        {
            return Direction::North;
        }
    }
};