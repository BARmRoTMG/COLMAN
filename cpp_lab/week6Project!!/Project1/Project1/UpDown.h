#pragma once
#include "IAiBehavior.h"
#include "PositionComponent.h"
#include "VelocityComponent.h"
#include "DrawableComponent.h"

struct UpDown : IAiBehavior
{
    void update(const std::vector<Entity*>& entities, Entity& self, float dt, int screenX, int screenY) override
    {
        auto pos = self.getComponent<PositionComponent>();
        auto vel = self.getComponent<VelocityComponent>();
        auto draw = self.getComponent<DrawableComponent>();
        if (!pos || !vel) return;

        float size = (draw) ? draw->m_size : 0.f;

        if (vel->m_vy == 0)
            vel->m_vy = vel->m_speed;

        if (pos->m_y >= screenY - size && vel->m_vy > 0)
        {
            vel->m_vy = -vel->m_speed;
        }
        else if (pos->m_y <= 0 && vel->m_vy < 0)
        {
            vel->m_vy = vel->m_speed;
        }
    }
};