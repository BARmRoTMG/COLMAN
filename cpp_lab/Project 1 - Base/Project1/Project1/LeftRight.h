#pragma once
#include "IAiBehavior.h"
#include "PositionComponent.h"
#include "VelocityComponent.h"
#include "DrawableComponent.h"
#include <SFML/System.hpp>

struct LeftRight : IAiBehavior
{
    void update( const std::vector<Entity*>& entities, Entity& self, float dt, sf::Vector2u screenSize ) override
    {
        auto pos = self.getComponent<PositionComponent>();
        auto vel = self.getComponent<VelocityComponent>();
        auto draw = self.getComponent<DrawableComponent>();
        if( pos && vel && draw )
        {
            vel->m_vy = 0.f;

            if( 0.f == pos->m_x )
                vel->m_vx = vel->m_speed;
            else if( screenSize.x == pos->m_x + draw->m_sprite.getLocalBounds().getSize().x )
                vel->m_vx = -vel->m_speed;
        }
    }
};