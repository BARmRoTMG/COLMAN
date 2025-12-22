#pragma once

#include "Component.h"
#include "ResourceManager.h"

struct SoundComponent : public Component
{
    SoundComponent( ResourceManager& rm, const std::string& filename )
    {
        m_buffer = rm.GetSound( filename );
        if( m_buffer )
            m_sound.setBuffer( *m_buffer );
    }

    std::shared_ptr<sf::SoundBuffer>    m_buffer;
    sf::Sound                           m_sound;
};