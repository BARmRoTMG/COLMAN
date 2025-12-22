#pragma once
#include <SFML/Graphics.hpp>
#include "Entity.h"
#include "PauseTagComponent.h"
#include "TextComponent.h"

class PauseSystem
{
public:
    void update( std::vector<Entity*>& entities, bool isPaused )
    {
        for( auto e : entities )
        {
            auto p = e->getComponent<PauseTagComponent>();
            auto t = e->getComponent<TextComponent>();
            if( p && t )
                t->m_visible = isPaused;
        }
    }
};