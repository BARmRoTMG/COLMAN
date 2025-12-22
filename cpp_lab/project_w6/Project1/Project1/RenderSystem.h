#pragma once

#include <SFML/Graphics.hpp>
#include "Entity.h"
#include "PositionComponent.h"
#include "DrawableComponent.h"

#include "TextComponent.h"

class RenderSystem
{
public:
    void render( sf::RenderWindow& window, const std::vector<Entity*>& entities )
    {
        for( auto e : entities )
        {
            auto pos = e->getComponent<PositionComponent>();
            auto draw = e->getComponent<DrawableComponent>();
            if( pos && draw )
            {
                draw->m_sprite.setColor( draw->m_color );
                draw->m_sprite.setPosition( pos->m_x, pos->m_y );
                window.draw( draw->m_sprite );
            }

            auto textComp = e->getComponent<TextComponent>();
            if( textComp && textComp->m_visible )
                window.draw( textComp->m_text );
        }
    }
};