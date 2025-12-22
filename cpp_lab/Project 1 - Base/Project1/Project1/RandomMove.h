#pragma once

#include "IAiBehavior.h"
#include "VelocityComponent.h"

struct RandomMove : IAiBehavior
{
    void update( const std::vector<Entity*>& entities, Entity& self, float dt ) override
    {
        m_timer -= dt;
        if( m_timer <= 0.f )
        {
            auto vel = self.getComponent<VelocityComponent>();
            if( vel )
            {
                vel->m_vx = ( rand() % 3 - 1 ) * vel->m_speed;
                vel->m_vy = ( rand() % 3 - 1 ) * vel->m_speed;
            }

            m_timer = 1.f;//can be randomized here again
        }
    }

    float m_timer = 1.f; //so direction will change every 1 second
};