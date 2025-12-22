#pragma once

#include "Entity.h"
#include "PositionComponent.h"
#include "DrawableComponent.h"

class BoundarySystem
{
public:
    void update( int screenX, int screenY, const std::vector<Entity*>& entities )
    {
        float entityPosX, entityPosY;
        int entitySize;
        for( auto e : entities )
        {
            auto pos = e->getComponent<PositionComponent>();
            auto draw = e->getComponent<DrawableComponent>();
            if( pos && draw )
            {
                entityPosX = pos->m_x;
                entityPosY = pos->m_y;
                entitySize = draw->m_size;

                if( entityPosX < 0 )                    entityPosX = 0;
                if( entityPosX > screenX - entitySize ) entityPosX = screenX - entitySize;
                if( entityPosY < 0 )                    entityPosY = 0;
                if( entityPosY > screenY - entitySize ) entityPosY = screenY - entitySize;

                pos->m_x = entityPosX;
                pos->m_y = entityPosY;
            }
        }
    }
};