#pragma once

#include <SFML/System/Vector2.hpp>
#include <SFML/Graphics.hpp>

struct Position
{
    sf::Vector2f value;
};

struct Velocity
{
    sf::Vector2f value;
    sf::Vector2f base;
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
    sf::Color color;
    sf::Vector2f size;
};
