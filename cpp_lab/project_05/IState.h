#pragma once
#include <SFML/Graphics.hpp>
#include <functional>
#include "EntityFactory.h"

typedef std::function<void()> Callback;

class IState
{
public:
    IState( EntityFactory& ef )
        : m_factory( ef )
    {
        
    }

    virtual ~IState()
    {
        for( auto p : m_entities )
            delete p;

        m_entities.clear();
    }

    virtual void InitEntities() = 0;
    virtual void handleEvent( const std::string& event ) = 0;
    virtual void update( float dt ) = 0;

public:
    EntityFactory&          m_factory;
    std::vector<Entity*>    m_entities;
};