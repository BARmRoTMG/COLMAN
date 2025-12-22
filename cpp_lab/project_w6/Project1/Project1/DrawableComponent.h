#pragma once

#include "Component.h"
#include "ResourceManager.h"

struct DrawableComponent : public Component
{
    DrawableComponent( ResourceManager& rm, const std::string& filename )
    {
        m_color = sf::Color::White;
        m_texture = rm.GetTexture( filename );
        if( m_texture )
            m_sprite.setTexture( *m_texture );
    }

    sf::Color                       m_color;
    std::shared_ptr<sf::Texture>    m_texture;
    sf::Sprite                      m_sprite;
};