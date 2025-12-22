#pragma once

#include "Entity.h"
#include "PositionComponent.h"
#include "VelocityComponent.h"

class MovementSystem
{
public:
    void update(const std::vector<Entity*>& entities, float dt)
    {
        for (auto e : entities)
        {
            auto pos = e->getComponent<PositionComponent>();
            auto vel = e->getComponent<VelocityComponent>();
            if (pos && vel)
            {
                pos->m_x += vel->m_vx * dt;
                pos->m_y += vel->m_vy * dt;
            }
        }
    }
};