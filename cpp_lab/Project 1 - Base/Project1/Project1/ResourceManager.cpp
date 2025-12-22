#include "ResourceManager.h"

//------------------------------------------------------------------------------------------------//
std::shared_ptr<sf::Texture> ResourceManager::GetTexture( const std::string& filename )
{
    //check if filename is in m_textures already, if yes - return a reference to it
    auto it = m_textures.find( filename );
    if( it != m_textures.end() )
        return it->second;

    //if not:
    // 1. create a new texture pointer
    // 2. load the texture to memory, if no success - return nullptr
    auto tex = std::make_shared<sf::Texture>();
    if( !tex->loadFromFile( filename ) )
    {
        //throw std::runtime_error( "Failed to load texture: " + filename );
        return nullptr;
    }

    // 3. if success then add it to the cache and return a reference to it
    m_textures[filename] = tex;
    return tex;
}
//------------------------------------------------------------------------------------------------//
std::shared_ptr<sf::Font> ResourceManager::GetFont( const std::string& filename )
{
    //check if filename is in m_fonts already, if yes - return a reference to it
    auto it = m_fonts.find( filename );
    if( it != m_fonts.end() )
        return it->second;

    //if not:
    // 1. create a new font pointer
    // 2. load the font to memory, if no success - return nullptr
    auto f = std::make_shared<sf::Font>();
    if( !f->loadFromFile( filename ) )
    {
        //throw std::runtime_error( "Failed to load font: " + filename );
        return nullptr;
    }

    // 3. if success then add it to the cache and return a reference to it
    m_fonts[filename] = f;
    return f;
}
//------------------------------------------------------------------------------------------------//
std::shared_ptr<sf::SoundBuffer> ResourceManager::GetSound( const std::string& filename )
{
    //check if filename is in m_sounds already, if yes - return a reference to it
    auto it = m_sounds.find( filename );
    if( it != m_sounds.end() )
        return it->second;

    //if not:
    // 1. create a new sound pointer
    // 2. load the sound to memory, if no success - return nullptr
    auto s = std::make_shared<sf::SoundBuffer>();
    if( !s->loadFromFile( filename ) )
    {
        //throw std::runtime_error( "Failed to load sound: " + filename );
        return nullptr;
    }

    // 3. if success then add it to the cache and return a reference to it
    m_sounds[filename] = s;
    return s;
}
//------------------------------------------------------------------------------------------------//