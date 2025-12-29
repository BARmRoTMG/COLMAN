#pragma once
#include "World.h"

class InteractionSystem
{
public:
    void Update( float dt, World& world )
    {
        handleTrafficLights( dt, world );
        handleCarBlocking( world );
    }

private:
    // =============================
    // Car <-> Traffic Light
    // =============================
    void handleTrafficLights( float dt, World& world )
    {
        
    }

    // =============================
    // Car <-> Car
    // =============================
    void handleCarBlocking( World& world )
    {
        
    } 

    // =============================
    // Helpers
    // =============================
    float getStopLine( Direction dir )
    {
        return 0.f;
    }

    bool hasReachedStopLine( Direction dir, const sf::Vector2f& pos )
    {
        return false;
    }

    TrafficLight* findLightForDirection( World& world, Direction dir )
    {
        return nullptr;
    }

    bool isSameLane( World& world, Entity a, Entity b )
    {
        return false;
    }

    bool isTooClose( World& world, Entity a, Entity b )
    {
        return false;
    }
};