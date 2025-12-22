#include "Simulator.h"

//------------------------------------------------------------------------------------------------//
Simulator::Simulator()
    : m_window( sf::VideoMode( 800, 800 ), "Traffic Intersection Simulator" )
{
    // Spawn some cars
    m_dispatcher.AddCar( { 1, Direction::North } );
    m_dispatcher.AddCar( { 2, Direction::East } );
    m_dispatcher.AddCar( { 3, Direction::South } );
    m_dispatcher.AddCar( { 4, Direction::West } );
}
//------------------------------------------------------------------------------------------------//
Simulator::~Simulator()
{
    
}
//------------------------------------------------------------------------------------------------//
void Simulator::Run()
{
    sf::Clock clock;

    while( m_window.isOpen() )
    {
        handleEvents();
        update( clock.restart().asSeconds() );
        render();
    }
}
//------------------------------------------------------------------------------------------------//
void Simulator::handleEvents()
{
    sf::Event event;

    while( m_window.pollEvent( event ) )
    {
        if( event.type == sf::Event::Closed )
            m_window.close();
    }
}
//------------------------------------------------------------------------------------------------//
void Simulator::update( float dt )
{
    m_lightTimer += dt;
    if( m_lightTimer > 3.f )
    {
        m_light = ( m_light == LightState::NS_Green ) ? LightState::EW_Green : LightState::NS_Green;
        m_lightTimer = 0.f;
    }

    m_dispatcher.Update( dt, m_light );
}
//------------------------------------------------------------------------------------------------//
void Simulator::render()
{
    m_window.clear( sf::Color( 30, 30, 30 ) );

    // Draw intersection
    sf::RectangleShape roadH( { 800, 100 } );
    roadH.setPosition( 0, 350 );
    roadH.setFillColor( sf::Color( 60, 60, 60 ) );

    sf::RectangleShape roadV( { 100, 800 } );
    roadV.setPosition( 350, 0 );
    roadV.setFillColor( sf::Color( 60, 60, 60 ) );

    m_window.draw( roadH );
    m_window.draw( roadV );

    // Draw lights
    sf::CircleShape lightShape( 10.f );
    lightShape.setPosition( 380, 320 );
    lightShape.setFillColor( m_light == LightState::NS_Green ? sf::Color::Green : sf::Color::Red );
    m_window.draw( lightShape );

    // Draw cars (just stacked rectangles)
    auto cars = m_dispatcher.GetWaitingCars();
    int offset = 0;
    for( const auto& c : cars )
    {
        sf::RectangleShape carShape( { 30, 15 } );
        carShape.setFillColor( sf::Color::Blue );
        carShape.setPosition( 100.f + offset * 35.f, 100.f );
        m_window.draw( carShape );
        offset++;
    }

    m_window.display();
}
//------------------------------------------------------------------------------------------------//