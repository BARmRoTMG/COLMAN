#include "CarDispatcher.h"

//------------------------------------------------------------------------------------------------//
void CarDispatcher::AddCar( const Car& car )
{
    m_queues[static_cast<int>( car.m_dir )].push( car );
}
//------------------------------------------------------------------------------------------------//
void CarDispatcher::Update( float dt, LightState light )
{
    // Accumulate wait time
    for( auto& q : m_queues )
    {
        std::queue<Car> temp;
        while( !q.empty() )
        {
            Car c = q.front();
            q.pop();
            c.m_waitTime += dt;
            temp.push( c );
        }

        q = temp;
    }

    // Release logic (very simple)
    if( light == LightState::NS_Green )
    {
        if( !m_queues[(int)Direction::North].empty() )
            m_queues[(int)Direction::North].pop();
        if( !m_queues[(int)Direction::South].empty() )
            m_queues[(int)Direction::South].pop();
    }
    else
    {
        if( !m_queues[(int)Direction::East].empty() )
            m_queues[(int)Direction::East].pop();
        if( !m_queues[(int)Direction::West].empty() )
            m_queues[(int)Direction::West].pop();
    }
}
//------------------------------------------------------------------------------------------------//
std::vector<Car> CarDispatcher::GetWaitingCars() const
{
    std::vector<Car> cars;
    for( const auto& q : m_queues )
    {
        std::queue<Car> copy = q;
        while( !copy.empty() )
        {
            cars.push_back( copy.front() );
            copy.pop();
        }
    }
    return cars;
}
//------------------------------------------------------------------------------------------------//