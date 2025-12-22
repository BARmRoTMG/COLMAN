#pragma once
#include <vector>
#include "Entity.h"
#include "PositionComponent.h"
#include "VelocityComponent.h"

class BoundarySystem
{
public:
    BoundarySystem( int minX, int maxX, int minY, int maxY )
        : m_minX( minX ), m_maxX( maxX ), m_minY( minY ), m_maxY( maxY )
    {
    }

    void update( std::vector<Entity*>& entities )
    {
        for (Entity* entity : entities)
        {
            PositionComponent* pos = entity->getComponent<PositionComponent>();
            VelocityComponent* vel = entity->getComponent<VelocityComponent>();

            if (!pos || !vel)
                continue;

            if (pos->m_x < m_minX)
            {
                pos->m_x = m_minX;
                vel->m_vx = 0;
            }
            else if (pos->m_x > m_maxX)
            {
                pos->m_x = m_maxX;
                vel->m_vx = 0;
            }

            if (pos->m_y < m_minY)
            {
                pos->m_y = m_minY;
                vel->m_vy = 0;
            }
            else if (pos->m_y > m_maxY)
            {
                pos->m_y = m_maxY;
                vel->m_vy = 0;
            }
        }
    }

private:
    int m_minX;
    int m_maxX;
    int m_minY;
    int m_maxY;
};
