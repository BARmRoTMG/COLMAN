#pragma once
#include <SFML/Graphics.hpp>
#include <functional>
#include "ResourceManager.h"
#include "EntityFactory.h"
#include "RenderSystem.h"

typedef std::function<void()> Callback;

class IState
{
public:
    IState( sf::RenderWindow& rw, ResourceManager& rm, EntityFactory& ef )
        : m_window( rw ), m_resourceManager( rm ), m_factory( ef )
    {
        
    }

    virtual ~IState()
    {
        for( auto p : m_entities )
            delete p;
    }

    virtual void InitEntities() = 0;
    virtual void handleEvent( const sf::Event& e ) = 0;
    virtual void update( float dt ) = 0;
    virtual void render() = 0;

protected:
    sf::RenderWindow&       m_window;
    ResourceManager&        m_resourceManager;
    EntityFactory&          m_factory;
    std::vector<Entity*>    m_entities;

protected:
    RenderSystem            m_renderSystem;
};