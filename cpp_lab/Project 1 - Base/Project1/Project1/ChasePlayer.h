#pragma once
#include "IAiBehavior.h"
#include "PositionComponent.h"
#include "VelocityComponent.h"

struct ChasePlayer : IAiBehavior
{
    ChasePlayer( const std::string& targetID ) : m_targetID( targetID ) {}

    void update( const std::vector<Entity*>& entities, Entity& self, float dt ) override
    {
        Entity* target = nullptr;
        for( auto e : entities )
        {
            if( e->m_name == m_targetID )
            {
                target = e;
                break;
            }
        }

        if( !target )
            return;

        auto pos = self.getComponent<PositionComponent>();
        auto vel = self.getComponent<VelocityComponent>();
        auto ppos = target->getComponent<PositionComponent>();

        if( pos && vel && ppos )
        {
            vel->m_vx = ( ppos->m_x > pos->m_x ) ? vel->m_speed : -vel->m_speed;
            vel->m_vy = ( ppos->m_y > pos->m_y ) ? vel->m_speed : -vel->m_speed;
        }
    }

    std::string m_targetID;
};