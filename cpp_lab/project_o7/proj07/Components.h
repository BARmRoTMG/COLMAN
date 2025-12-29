#pragma once

struct Position
{
    float x;
    float y;
};

struct Velocity
{
    float valueX;
    float valueY;
    float baseX;
    float baseY;
};

enum class Direction
{
    North = 0,
    East,
    South,
    West,
    Total
};

struct DirectionComponent
{
    Direction value;
};

struct CarTag {};

struct CarState
{
    float waitTime = 0.f;
    bool crossing = false;
};

struct TrafficLight
{
    Direction lane;
    bool green = false;
};

struct TrafficLightController
{
    Direction current = Direction::North;
    float timer = 0.f;
};

struct Drawable
{
    float sizeX;
    float sizeY;
};
