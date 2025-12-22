#pragma once

#include "Entity.h"
#include "VelocityComponent.h"
#include "InputComponent.h"
#include "InputSystem.h"
#include "SoundComponent.h"

class PlayerControlSystem
{
public:
    void update( const InputSystem& input, const std::vector<Entity*>& entities )
    {
        bool wasMoving;
        bool moving;
        for( auto e : entities )
        {
            auto in = e->getComponent<InputComponent>();
            auto vel = e->getComponent<VelocityComponent>();
            if( in && vel )
            {
                wasMoving = vel->m_vx || vel->m_vy;

                vel->m_vx = vel->m_vy = 0;

                if( input.isKeyPressed( sf::Keyboard::Right ) ) vel->m_vx = vel->m_speed;
                if( input.isKeyPressed( sf::Keyboard::Left ) ) vel->m_vx = -vel->m_speed;
                if( input.isKeyPressed( sf::Keyboard::Down ) ) vel->m_vy = vel->m_speed;
                if( input.isKeyPressed( sf::Keyboard::Up ) ) vel->m_vy = -vel->m_speed;

                moving = vel->m_vx || vel->m_vy;

                if( moving && !wasMoving )
                {
                    auto s = e->getComponent<SoundComponent>();
                    if( s )
                        s->m_sound.play();
                }
            }
        }
    }
};