#pragma once

#include "AIComponent.h"
#include "DrawableComponent.h"
#include "Entity.h"

class BehaviorVisualizerSystem
{
public:
    void update( std::vector<Entity*>& entities )
    {
        for( auto e : entities )
        {
            auto ai = e->getComponent<AIComponent>();
            auto draw = e->getComponent<DrawableComponent>();

            if( ai && draw )
            {
                switch( ai->m_type )
                {
                case AIComponent::BehaviorType::Idle:
                    draw->m_color = sf::Color::White;
                    break;
                case AIComponent::BehaviorType::Random:
                    draw->m_color = sf::Color::Red;
                    break;
                case AIComponent::BehaviorType::LeftRight:
                    draw->m_color = sf::Color::Blue;
                    break;
                case AIComponent::BehaviorType::Chase:
                    draw->m_color = sf::Color::Yellow;
                    break;
                }
            }
        }
    }
};