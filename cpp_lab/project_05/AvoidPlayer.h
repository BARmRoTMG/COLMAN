#pragma once
#include "IAiBehavior.h"
#include "PositionComponent.h"
#include "VelocityComponent.h"

struct AvoidPlayer : IAiBehavior
{
    AvoidPlayer( const std::string& targetID ) : m_targetID(targetID) {}

    void update( const std::vector<Entity*>& entities, Entity& self, float dt, int screenX, int screenY ) override
    {
        Entity* target = nullptr;
        for (auto* e : entities)
        {
            if (e->m_name == m_targetID)
            {
                target = e;
                break;
            }
        }

        if (!target)
            return;

        auto myPos = self.getComponent<PositionComponent>();
        auto myVel = self.getComponent<VelocityComponent>();
        auto targetPos = target->getComponent<PositionComponent>();

        if (!myPos || !myVel || !targetPos) return;

        float dirX = myPos->m_x - targetPos->m_x;
        float dirY = myPos->m_y - targetPos->m_y;

        float length = std::sqrt(dirX * dirX + dirY * dirY);

        if (length != 0)
        {
            dirX /= length;
            dirY /= length;

            myVel->m_vx = dirX * myVel->m_speed;
            myVel->m_vy = dirY * myVel->m_speed;
        }
    }

    std::string m_targetID;
};