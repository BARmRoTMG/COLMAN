#pragma once

#include <SFML/Graphics.hpp>
#include "Entity.h"
#include "PositionComponent.h"
#include "DrawableComponent.h"

class BoundarySystem
{
public:
    void update( const sf::RenderWindow& window, const std::vector<Entity*>& entities )
    {
        sf::Vector2u windowSize = window.getSize();
        sf::Vector2f entityPos;
        sf::Vector2f entitySize;
        for( auto e : entities )
        {
            auto pos = e->getComponent<PositionComponent>();
            auto draw = e->getComponent<DrawableComponent>();
            if( pos && draw )
            {
                entityPos = { pos->m_x, pos->m_y };
                entitySize = draw->m_sprite.getLocalBounds().getSize();

                if( entityPos.x < 0 )                           entityPos.x = 0;
                if( entityPos.x > windowSize.x - entitySize.x ) entityPos.x = windowSize.x - entitySize.x;
                if( entityPos.y < 0 )                           entityPos.y = 0;
                if( entityPos.y > windowSize.y - entitySize.y ) entityPos.y = windowSize.y - entitySize.y;

                pos->m_x = entityPos.x;
                pos->m_y = entityPos.y;
            }
        }
    }
};