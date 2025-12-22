#pragma once

#include "IAiBehavior.h"
#include "VelocityComponent.h"

struct Idle : IAiBehavior
{
    void update( const std::vector<Entity*>& entities, Entity& self, float dt, sf::Vector2u screenSize ) override
    {
        auto vel = self.getComponent<VelocityComponent>();
        if( vel )
        {
            vel->m_vx = vel->m_vy = 0.f;
        }
    }
};