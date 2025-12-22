#pragma once

#include "Component.h"
#include "ResourceManager.h"

struct TextComponent : public Component
{
    TextComponent( ResourceManager& rm, const std::string& fontFile )
    {
        m_font = rm.GetFont( fontFile );

        if( m_font )
            m_text.setFont( *m_font );

        m_visible = false;
    }

    sf::Text                    m_text;
    std::shared_ptr<sf::Font>   m_font;
    bool                        m_visible;
};