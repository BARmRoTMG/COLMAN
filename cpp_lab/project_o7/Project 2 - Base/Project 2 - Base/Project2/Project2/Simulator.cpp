#include "Simulator.h"

//------------------------------------------------------------------------------------------------//
Simulator::Simulator()
    : m_window( sf::VideoMode( 800, 800 ), "Traffic Intersection Simulator" )
{
    Entity e;
    // create intersection
    e = m_world.CreateEntity();
    m_world.AddComponent<Drawable>( e, { sf::Color( 60, 60, 60 ), { 800, 100 } } );
    m_world.AddComponent<Position>( e, { { 0, 350 } } );

    e = m_world.CreateEntity();
    m_world.AddComponent<Drawable>( e, { sf::Color( 60, 60, 60 ), { 100, 800 } } );
    m_world.AddComponent<Position>( e, { { 350, 0 } } );

    // create lanes
    e = m_world.CreateEntity();
    m_world.AddComponent<Drawable>( e, { sf::Color::White, { 350, 4 } } );
    m_world.AddComponent<Position>( e, { { 0, 398 } } );

    e = m_world.CreateEntity();
    m_world.AddComponent<Drawable>( e, { sf::Color::White, { 350, 4 } } );
    m_world.AddComponent<Position>( e, { { 450, 398 } } );

    e = m_world.CreateEntity();
    m_world.AddComponent<Drawable>( e, { sf::Color::White, { 4, 350 } } );
    m_world.AddComponent<Position>( e, { { 398, 0 } } );

    e = m_world.CreateEntity();
    m_world.AddComponent<Drawable>( e, { sf::Color::White, { 4, 350 } } );
    m_world.AddComponent<Position>( e, { { 398, 450 } } );

    // create lights
    e = m_world.CreateEntity();
    m_world.AddComponent<Drawable>( e, { sf::Color::Red, { 10, 10 } } );
    m_world.AddComponent<Position>( e, { { 414, 430 } } );
    m_world.AddComponent<TrafficLight>( e, { Direction::North, false } );

    e = m_world.CreateEntity();
    m_world.AddComponent<Drawable>( e, { sf::Color::Red, { 10, 10 } } );
    m_world.AddComponent<Position>( e, { { 350, 414 } } );
    m_world.AddComponent<TrafficLight>( e, { Direction::East, false } );

    e = m_world.CreateEntity();
    m_world.AddComponent<Drawable>( e, { sf::Color::Green, { 10, 10 } } );
    m_world.AddComponent<Position>( e, { { 364, 350 } } );
    m_world.AddComponent<TrafficLight>( e, { Direction::South, true } );

    e = m_world.CreateEntity();
    m_world.AddComponent<Drawable>( e, { sf::Color::Red, { 10, 10 } } );
    m_world.AddComponent<Position>( e, { { 430, 364 } } );
    m_world.AddComponent<TrafficLight>( e, { Direction::West, false } );

    // create light controller
    e = m_world.CreateEntity();
    m_world.AddComponent<TrafficLightController>( e, {} );

    // create cars
    e = m_world.CreateEntity();
    m_world.AddComponent<Drawable>( e, { sf::Color::Blue, { 15, 30 } } );
    m_world.AddComponent<Position>( e, { { 416, 700 } } );
    m_world.AddComponent<Velocity>( e, { { 0.f, -50.f }, { 0.f, -50.f } } );
    m_world.AddComponent<DirectionComponent>( e, { Direction::North } );
    m_world.AddComponent<CarTag>( e, {} );
    m_world.AddComponent<CarState>( e, {} );

    e = m_world.CreateEntity();
    m_world.AddComponent<Drawable>( e, { sf::Color::Blue, { 30, 15 } } );
    m_world.AddComponent<Position>( e, { { 100, 416 } } );
    m_world.AddComponent<Velocity>( e, { { 50.f, 0.f }, { 50.f, 0.f } } );
    m_world.AddComponent<DirectionComponent>( e, { Direction::East } );
    m_world.AddComponent<CarTag>( e, {} );
    m_world.AddComponent<CarState>( e, {} );

    e = m_world.CreateEntity();
    m_world.AddComponent<Drawable>( e, { sf::Color::Blue, { 15, 30 } } );
    m_world.AddComponent<Position>( e, { { 366, 100 } } );
    m_world.AddComponent<Velocity>( e, { { 0.f, 50.f }, { 0.f, 50.f } } );
    m_world.AddComponent<DirectionComponent>( e, { Direction::South } );
    m_world.AddComponent<CarTag>( e, {} );
    m_world.AddComponent<CarState>( e, {} );

    e = m_world.CreateEntity();
    m_world.AddComponent<Drawable>( e, { sf::Color::Blue, { 30, 15 } } );
    m_world.AddComponent<Position>( e, { { 700, 366 } } );
    m_world.AddComponent<Velocity>( e, { { -50.f, 0.f }, { -50.f, 0.f } } );
    m_world.AddComponent<DirectionComponent>( e, { Direction::West } );
    m_world.AddComponent<CarTag>( e, {} );
    m_world.AddComponent<CarState>( e, {} );
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
    m_trafficSystem.Update( dt, m_world );
    m_movementSystem.Update( dt, m_world );
    m_interactionSystem.Update( dt, m_world );
    m_cleanupSystem.Update( m_world, m_window );
}
//------------------------------------------------------------------------------------------------//
void Simulator::render()
{
    m_window.clear( sf::Color( 30, 30, 30 ) );
    m_renderSystem.Update( m_world, m_window );
    m_window.display();
}
//------------------------------------------------------------------------------------------------//