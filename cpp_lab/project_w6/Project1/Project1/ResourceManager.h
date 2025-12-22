#pragma once

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <unordered_map>
#include <string>
#include <memory>

class ResourceManager
{
public:
    std::shared_ptr<sf::Texture>        GetTexture( const std::string& filename );
    std::shared_ptr<sf::Font>           GetFont( const std::string& filename );
    std::shared_ptr<sf::SoundBuffer>    GetSound( const std::string& filename );

private:
    std::unordered_map<std::string, std::shared_ptr<sf::Texture>>       m_textures;
    std::unordered_map<std::string, std::shared_ptr<sf::Font>>          m_fonts;
    std::unordered_map<std::string, std::shared_ptr<sf::SoundBuffer>>   m_sounds;
};