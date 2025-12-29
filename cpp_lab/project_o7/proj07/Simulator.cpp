#include "Simulator.h"

//------------------------------------------------------------------------------------------------//
Simulator::Simulator()
{
    Entity e;

    // create lights
    e = m_world.CreateEntity();//1
    m_world.AddComponent<Position>( e, { 414, 430 } );
    m_world.AddComponent<TrafficLight>( e, { Direction::North, false } );

    e = m_world.CreateEntity();//2
    m_world.AddComponent<Drawable>( e, { 10, 10 } );
    m_world.AddComponent<Position>( e, { 350, 414 } );
    m_world.AddComponent<TrafficLight>( e, { Direction::East, false } );

    e = m_world.CreateEntity();//3
    m_world.AddComponent<Drawable>( e, { 10, 10 } );
    m_world.AddComponent<Position>( e, { 364, 350 } );
    m_world.AddComponent<TrafficLight>( e, { Direction::South, true } );

    e = m_world.CreateEntity();//4
    m_world.AddComponent<Drawable>( e, { 10, 10 } );
    m_world.AddComponent<Position>( e, { 430, 364 } );
    m_world.AddComponent<TrafficLight>( e, { Direction::West, false } );

    // create light controller
    e = m_world.CreateEntity();//5
    m_world.AddComponent<TrafficLightController>( e, {} );

    // create cars
    e = m_world.CreateEntity();//6
    m_world.AddComponent<Drawable>( e, { 15, 30 } );
    m_world.AddComponent<Position>( e, { 416, 700 } );
    m_world.AddComponent<Velocity>( e, { 0.f, -50.f, 0.f, -50.f } );
    m_world.AddComponent<DirectionComponent>( e, { Direction::North } );
    m_world.AddComponent<CarTag>( e, {} );
    m_world.AddComponent<CarState>( e, {} );

    e = m_world.CreateEntity();//7
    m_world.AddComponent<Drawable>( e, { 30, 15 } );
    m_world.AddComponent<Position>( e, { 100, 416 } );
    m_world.AddComponent<Velocity>( e, { 50.f, 0.f, 50.f, 0.f } );
    m_world.AddComponent<DirectionComponent>( e, { Direction::East } );
    m_world.AddComponent<CarTag>( e, {} );
    m_world.AddComponent<CarState>( e, {} );

    e = m_world.CreateEntity();//8
    m_world.AddComponent<Drawable>( e, { 15, 30 } );
    m_world.AddComponent<Position>( e, { 366, 100 } );
    m_world.AddComponent<Velocity>( e, { 0.f, 50.f, 0.f, 50.f } );
    m_world.AddComponent<DirectionComponent>( e, { Direction::South } );
    m_world.AddComponent<CarTag>( e, {} );
    m_world.AddComponent<CarState>( e, {} );

    e = m_world.CreateEntity();//9
    m_world.AddComponent<Drawable>( e, { 30, 15 } );
    m_world.AddComponent<Position>( e, { 700, 366 } );
    m_world.AddComponent<Velocity>( e, { -50.f, 0.f, -50.f, 0.f } );
    m_world.AddComponent<DirectionComponent>( e, { Direction::West } );
    m_world.AddComponent<CarTag>( e, {} );
    m_world.AddComponent<CarState>( e, {} );

    e = m_world.CreateEntity();//10
    m_world.AddComponent<Drawable>( e, { 15, 30 } );
    m_world.AddComponent<Position>( e, { 416, 750 } );
    m_world.AddComponent<Velocity>( e, { 0.f, -50.f, 0.f, -50.f } );
    m_world.AddComponent<DirectionComponent>( e, { Direction::North } );
    m_world.AddComponent<CarTag>( e, {} );
    m_world.AddComponent<CarState>( e, {} );

    e = m_world.CreateEntity();//11
    m_world.AddComponent<Drawable>( e, { 30, 15 } );
    m_world.AddComponent<Position>( e, { 50, 416 } );
    m_world.AddComponent<Velocity>( e, { 50.f, 0.f, 50.f, 0.f } );
    m_world.AddComponent<DirectionComponent>( e, { Direction::East } );
    m_world.AddComponent<CarTag>( e, {} );
    m_world.AddComponent<CarState>( e, {} );

    e = m_world.CreateEntity();//12
    m_world.AddComponent<Drawable>( e, { 15, 30 } );
    m_world.AddComponent<Position>( e, { 366, 50 } );
    m_world.AddComponent<Velocity>( e, { 0.f, 50.f, 0.f, 50.f } );
    m_world.AddComponent<DirectionComponent>( e, { Direction::South } );
    m_world.AddComponent<CarTag>( e, {} );
    m_world.AddComponent<CarState>( e, {} );

    e = m_world.CreateEntity();//13
    m_world.AddComponent<Drawable>( e, { 30, 15 } );
    m_world.AddComponent<Position>( e, { 750, 366 } );
    m_world.AddComponent<Velocity>( e, { -50.f, 0.f, -50.f, 0.f } );
    m_world.AddComponent<DirectionComponent>( e, { Direction::West } );
    m_world.AddComponent<CarTag>( e, {} );
    m_world.AddComponent<CarState>( e, {} );
}
//------------------------------------------------------------------------------------------------//
Simulator::~Simulator()
{

}
//------------------------------------------------------------------------------------------------//
void Simulator::Update( float dt )
{
    m_trafficSystem.Update( dt, m_world );
    m_movementSystem.Update( dt, m_world );
    m_interactionSystem.Update( dt, m_world );
    m_cleanupSystem.Update( m_world );
}
//------------------------------------------------------------------------------------------------//