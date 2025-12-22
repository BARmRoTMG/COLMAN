#include "EntityFactory.h"
#include "PositionComponent.h"
#include "VelocityComponent.h"
#include "InputComponent.h"
#include "DrawableComponent.h"
#include "SoundComponent.h"
#include "AIComponent.h"
#include "RandomMove.h"
#include "ChasePlayer.h"
#include "PauseTagComponent.h"
#include "TextComponent.h"

//------------------------------------------------------------------------------------------------//
EntityFactory::EntityFactory( ResourceManager& rm )
	: m_rm( rm )
{
}
//------------------------------------------------------------------------------------------------//
Entity* EntityFactory::Create( const std::string& type, sf::RenderWindow& wnd )
{
    Entity* e = nullptr;

    if( type == "player" )
    {
        e = new Entity( "player" );
        e->addComponent<PositionComponent>( 200.f, 200.f );
        e->addComponent<VelocityComponent>( 0.f, 0.f, 100.f );
        e->addComponent<InputComponent>();
        e->addComponent<DrawableComponent>( m_rm, "assets/player.png" );
        e->addComponent<SoundComponent>( m_rm, "assets/ui_click.wav" );
    }
    else if( type == "enemy_random" )
    {
        e = new Entity( "enemy_random" );
        e->addComponent<PositionComponent>( 400.f, 100.f );
        e->addComponent<VelocityComponent>( 0.f, 0.f, 40.f );
        e->addComponent<DrawableComponent>( m_rm, "assets/enemy.png" );
        e->addComponent<AIComponent>( std::make_unique<RandomMove>() );
    }
    else if( type == "enemy_chase" )
    {
        e = new Entity( "enemy_chase" );
        e->addComponent<PositionComponent>( 400.f, 100.f );
        e->addComponent<VelocityComponent>( 0.f, 0.f, 40.f );
        e->addComponent<DrawableComponent>( m_rm, "assets/enemy.png" );
        e->addComponent<AIComponent>( std::make_unique<ChasePlayer>( "player" ) );
    }
    else if( type == "text_pause" )
    {
        //init the entity
        e = new Entity( "text_pause" );
        e->addComponent<PauseTagComponent>();
        e->addComponent<TextComponent>( m_rm, "assets/arial.ttf" );

        //init the txt object
        auto txt = e->getComponent<TextComponent>();
        txt->m_text.setString( "PAUSED" );
        txt->m_text.setCharacterSize( 48 );
        txt->m_text.setFillColor( sf::Color::White );
        txt->m_text.setStyle( sf::Text::Bold );
        txt->m_visible = false;

        //make it centered
        auto bounds = txt->m_text.getLocalBounds();
        txt->m_text.setOrigin( bounds.left + bounds.width / 2.f, bounds.top + bounds.height / 2.f );
        txt->m_text.setPosition( wnd.getSize().x / 2.f, wnd.getSize().y / 2.f );
    }

    return e;
}
//------------------------------------------------------------------------------------------------//