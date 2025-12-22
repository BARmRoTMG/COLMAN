#pragma once
#include "IAiBehavior.h"
#include "PositionComponent.h"
#include "VelocityComponent.h"
#include "DrawableComponent.h"
#include <cmath>

struct AvoidPlayer : IAiBehavior
{
    AvoidPlayer(const std::string& targetID) : m_targetID(targetID) {}

    void update(const std::vector<Entity*>& entities, Entity& self, float dt, int screenX, int screenY) override
    {
        auto myPos = self.getComponent<PositionComponent>();
        auto myVel = self.getComponent<VelocityComponent>();
        auto myDraw = self.getComponent<DrawableComponent>();
        if (!myPos || !myVel) return;

        float size = (myDraw) ? myDraw->m_size : 0.f;

        Entity* target = nullptr;
        for (auto* e : entities)
        {
            if (e->m_name == m_targetID)
            {
                target = e;
                break;
            }
        }

        if (target)
        {
            auto targetPos = target->getComponent<PositionComponent>();
            if (targetPos)
            {
                float dirX = myPos->m_x - targetPos->m_x;
                float dirY = myPos->m_y - targetPos->m_y;

                myVel->m_vx = (dirX > 0) ? myVel->m_speed : ((dirX < 0) ? -myVel->m_speed : 0);
                myVel->m_vy = (dirY > 0) ? myVel->m_speed : ((dirY < 0) ? -myVel->m_speed : 0);

                if (myPos->m_x <= 0 && myVel->m_vx < 0)
                    myVel->m_vx = 0;
                if (myPos->m_x >= screenX - size && myVel->m_vx > 0)
                    myVel->m_vx = 0;
                if (myPos->m_y <= 0 && myVel->m_vy < 0)
                    myVel->m_vy = 0;
                if (myPos->m_y >= screenY - size && myVel->m_vy > 0)
                    myVel->m_vy = 0;
            }
        }
    }

    std::string m_targetID;
};