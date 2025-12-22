#pragma once
#include "Entity.h"
#include "AIComponent.h"

class AISystem
{
public:
    void update( const std::vector<Entity*>& entities, float dt, int screenX, int screenY )
    {
        for( auto e : entities )
        {
            auto ai = e->getComponent<AIComponent>();
            if( ai && ai->m_behavior )
            {
                ai->m_behavior->update( entities, *e, dt, screenX, screenY );
            }
        }
    }
};