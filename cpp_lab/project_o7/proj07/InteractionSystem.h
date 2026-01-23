#pragma once
#include "World.h"

class InteractionSystem
{
public:
    void Update(float dt, World& world)
    {
        auto cars = world.View<CarTag, Position, Velocity, DirectionComponent, CarState>();
        auto lights = world.View<TrafficLight>();

        for (auto car : cars)
        {
            auto& pos = world.GetComponent<Position>(car);
            auto& vel = world.GetComponent<Velocity>(car);
            auto& dir = world.GetComponent<DirectionComponent>(car);
            auto& state = world.GetComponent<CarState>(car);

            bool passedIntersection = HasPassedIntersection(pos, dir.value);

            if (passedIntersection)
            {
                state.crossing = true;
                vel.valueX = vel.baseX;
                vel.valueY = vel.baseY;
            }
            else
            {
                if (state.crossing)
                {
                    vel.valueX = vel.baseX;
                    vel.valueY = vel.baseY;
                }
                else
                {
                    bool hasGreenLight = false;

                    for (auto light : lights)
                    {
                        auto& trafficLight = world.GetComponent<TrafficLight>(light);
                        if (trafficLight.lane == dir.value)
                        {
                            hasGreenLight = trafficLight.green;
                            break;
                        }
                    }

                    if (hasGreenLight)
                    {
                        vel.valueX = vel.baseX;
                        vel.valueY = vel.baseY;
                    }
                    else
                    {
                        vel.valueX = 0.0f;
                        vel.valueY = 0.0f;
                        state.waitTime += dt;
                    }
                }
            }
        }
    }

private:
    bool HasPassedIntersection(const Position& pos, Direction dir)
    {
        const float INTERSECTION_START = 350.0f;
        const float INTERSECTION_END = 430.0f;

        switch (dir)
        {
        case Direction::North:
            return pos.y < INTERSECTION_START;

        case Direction::South:
            return pos.y > INTERSECTION_END;

        case Direction::East:
            return pos.x > INTERSECTION_END;

        case Direction::West:
            return pos.x < INTERSECTION_START;

        default:
            return false;
        }
    }
};