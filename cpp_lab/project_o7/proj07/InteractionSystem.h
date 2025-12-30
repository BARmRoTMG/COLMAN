#pragma once
#include "World.h"
#include <cmath>

class InteractionSystem
{
public:
    void Update(float dt, World& world)
    {
        handleTrafficLights(dt, world);
        handleCarBlocking(world);
    }

private:
    // =============================
    // Car <-> Traffic Light
    // =============================
    void handleTrafficLights(float dt, World& world)
    {
        auto cars = world.View<CarTag, Position, Velocity, DirectionComponent, CarState>();

        for (Entity carEntity : cars)
        {
            auto& pos = world.GetComponent<Position>(carEntity);
            auto& vel = world.GetComponent<Velocity>(carEntity);
            auto& dir = world.GetComponent<DirectionComponent>(carEntity);
            auto& state = world.GetComponent<CarState>(carEntity);

            // אם הרכב עבר את קו העצירה, הוא ממשיך לנסוע
            if (state.crossing)
            {
                vel.valueX = vel.baseX;
                vel.valueY = vel.baseY;
                continue;
            }

            // מצא את הרמזור בכיוון הזה
            TrafficLight* light = findLightForDirection(world, dir.value);

            if (light == nullptr)
                continue;

            // בדוק אם הרכב הגיע לקו העצירה
            if (hasReachedStopLine(dir.value, pos))
            {
                // אם הגיע לקו, הוא נכנס לצומת
                state.crossing = true;
                vel.valueX = vel.baseX;
                vel.valueY = vel.baseY;
            }
            else
            {
                // עדיין לא הגיע לקו - בדוק את הרמזור
                if (!light->green)
                {
                    // אדום - עצור
                    vel.valueX = 0.0f;
                    vel.valueY = 0.0f;
                    state.waitTime += dt;
                }
                else
                {
                    // ירוק - נסע
                    vel.valueX = vel.baseX;
                    vel.valueY = vel.baseY;
                }
            }
        }
    }

    // =============================
    // Car <-> Car
    // =============================
    void handleCarBlocking(World& world)
    {
        auto cars = world.View<CarTag, Position, Velocity, DirectionComponent, CarState>();

        for (Entity carA : cars)
        {
            auto& velA = world.GetComponent<Velocity>(carA);
            auto& stateA = world.GetComponent<CarState>(carA);

            // אם הרכב עומד בגלל רמזור, בדוק אם יש רכבים מאחוריו
            if (velA.valueX == 0.0f && velA.valueY == 0.0f && !stateA.crossing)
            {
                for (Entity carB : cars)
                {
                    if (carA == carB)
                        continue;

                    // אם באותו נתיב וקרוב מדי
                    if (isSameLane(world, carA, carB) && isTooClose(world, carA, carB))
                    {
                        auto& velB = world.GetComponent<Velocity>(carB);
                        velB.valueX = 0.0f;
                        velB.valueY = 0.0f;
                    }
                }
            }
        }
    }

    // =============================
    // Helpers
    // =============================
    float getStopLine(Direction dir)
    {
        const float stopLineDistance = 150.0f; // מרחק מהמרכז

        switch (dir)
        {
        case Direction::North: return -stopLineDistance; // y
        case Direction::South: return stopLineDistance;  // y
        case Direction::East:  return stopLineDistance;  // x
        case Direction::West:  return -stopLineDistance; // x
        default: return 0.0f;
        }
    }

    bool hasReachedStopLine(Direction dir, const Position& pos)
    {
        float stopLine = getStopLine(dir);

        switch (dir)
        {
        case Direction::North: return pos.y <= stopLine; // נוסע למעלה (y יורד)
        case Direction::South: return pos.y >= stopLine; // נוסע למטה (y עולה)
        case Direction::East:  return pos.x >= stopLine; // נוסע ימינה (x עולה)
        case Direction::West:  return pos.x <= stopLine; // נוסע שמאלה (x יורד)
        default: return false;
        }
    }

    TrafficLight* findLightForDirection(World& world, Direction dir)
    {
        auto lights = world.View<TrafficLight>();

        for (Entity lightEntity : lights)
        {
            auto& light = world.GetComponent<TrafficLight>(lightEntity);
            if (light.lane == dir)
            {
                return &light;
            }
        }

        return nullptr;
    }

    bool isSameLane(World& world, Entity a, Entity b)
    {
        if (!world.HasComponent<DirectionComponent>(a) ||
            !world.HasComponent<DirectionComponent>(b))
            return false;

        auto& dirA = world.GetComponent<DirectionComponent>(a);
        auto& dirB = world.GetComponent<DirectionComponent>(b);

        return dirA.value == dirB.value;
    }

    bool isTooClose(World& world, Entity a, Entity b)
    {
        auto& posA = world.GetComponent<Position>(a);
        auto& posB = world.GetComponent<Position>(b);

        float dx = posA.x - posB.x;
        float dy = posA.y - posB.y;
        float distSq = dx * dx + dy * dy;

        const float minDistance = 80.0f; // מרחק מינימלי בין רכבים

        return distSq < (minDistance * minDistance);
    }
};