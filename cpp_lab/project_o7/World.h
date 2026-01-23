#pragma once
#include "Components.h"
#include <unordered_map>
#include <set>
#include <vector>
#include <cstdint>

using Entity = std::uint32_t;

class World
{
public:
    // ===== Entity Management =====
    Entity CreateEntity()
    {
        ++m_nextEntity;
        m_aliveEntities.insert( m_nextEntity );
        return m_nextEntity;
    }

    void DestroyEntity( Entity e )
    {
        m_aliveEntities.erase( e );

        m_positions.erase( e );
        m_velocities.erase( e );
        m_directions.erase( e );
        m_cars.erase( e );
        m_carStates.erase( e );
        m_lights.erase( e );
        m_lightControllers.erase( e );
        m_drawables.erase( e );
    }

    bool IsAlive( Entity e ) const
    {
        return m_aliveEntities.find( e ) != m_aliveEntities.end();
    }

    const std::set<Entity>& Entities() const
    {
        return m_aliveEntities;
    }

public:
    // ===== Component Management =====
    template<typename T>
    void AddComponent( Entity e, const T& component );

    template<typename T>
    bool HasComponent( Entity e ) const;

    template<typename T>
    T& GetComponent( Entity e );

    template<typename T>
    const T& GetComponent( Entity e ) const;

    // ===== Views (Queries) =====
    template<typename... Components>
    std::vector<Entity> View() const
    {
        std::vector<Entity> result;

        for( Entity e : m_aliveEntities )
        {
            if( ( HasComponent<Components>( e ) && ... ) )
                result.push_back( e );
        }

        return result;
    }

private:
    Entity m_nextEntity = 0;
    std::set<Entity> m_aliveEntities;

    std::unordered_map<Entity, Position>            m_positions;
    std::unordered_map<Entity, Velocity>            m_velocities;
    std::unordered_map<Entity, DirectionComponent>  m_directions;
    std::unordered_map<Entity, CarTag>              m_cars;
    std::unordered_map<Entity, CarState>            m_carStates;
    std::unordered_map<Entity, TrafficLight>        m_lights;
    std::unordered_map<Entity, TrafficLightController> m_lightControllers;
    std::unordered_map<Entity, Drawable>            m_drawables;
};

// ===== AddComponent Specialization =====
template<> inline
void World::AddComponent( Entity e, const Position& c ) { m_positions[e] = c; }

template<> inline
void World::AddComponent( Entity e, const Velocity& c ) { m_velocities[e] = c; }

template<> inline
void World::AddComponent( Entity e, const DirectionComponent& c ) { m_directions[e] = c; }

template<> inline
void World::AddComponent( Entity e, const CarTag& c ) { m_cars[e] = c; }

template<> inline
void World::AddComponent( Entity e, const CarState& c ) { m_carStates[e] = c; }

template<> inline
void World::AddComponent( Entity e, const TrafficLight& c ) { m_lights[e] = c; }

template<> inline
void World::AddComponent( Entity e, const TrafficLightController& c ) { m_lightControllers[e] = c; }

template<> inline
void World::AddComponent( Entity e, const Drawable& c ) { m_drawables[e] = c; }

// ===== HasComponent Specialization =====
template<> inline
bool World::HasComponent<Position>( Entity e ) const { return m_positions.find( e ) != m_positions.end(); }

template<> inline
bool World::HasComponent<Velocity>( Entity e ) const { return m_velocities.find( e ) != m_velocities.end(); }

template<> inline
bool World::HasComponent<DirectionComponent>( Entity e ) const { return m_directions.find( e ) != m_directions.end(); }

template<> inline
bool World::HasComponent<CarTag>( Entity e ) const { return m_cars.find( e ) != m_cars.end(); }

template<> inline
bool World::HasComponent<CarState>( Entity e ) const { return m_carStates.find( e ) != m_carStates.end(); }

template<> inline
bool World::HasComponent<TrafficLight>( Entity e ) const { return m_lights.find( e ) != m_lights.end(); }

template<> inline
bool World::HasComponent<TrafficLightController>( Entity e ) const { return m_lightControllers.find( e ) != m_lightControllers.end(); }

template<> inline
bool World::HasComponent<Drawable>( Entity e ) const { return m_drawables.find( e ) != m_drawables.end(); }

// ===== GetComponent Specialization =====
template<> inline
Position& World::GetComponent( Entity e ) { return m_positions.at( e ); }

template<> inline
Velocity& World::GetComponent( Entity e ) { return m_velocities.at( e ); }

template<> inline
DirectionComponent& World::GetComponent( Entity e ) { return m_directions.at( e ); }

template<> inline
CarTag& World::GetComponent( Entity e ) { return m_cars.at( e ); }

template<> inline
CarState& World::GetComponent( Entity e ) { return m_carStates.at( e ); }

template<> inline
TrafficLight& World::GetComponent( Entity e ) { return m_lights.at( e ); }

template<> inline
TrafficLightController& World::GetComponent( Entity e ) { return m_lightControllers.at( e ); }

template<> inline
Drawable& World::GetComponent( Entity e ) { return m_drawables.at( e ); }

// ===== const GetComponent const Specialization =====
template<> inline
const Position& World::GetComponent( Entity e ) const { return m_positions.at( e ); }

template<> inline
const Velocity& World::GetComponent( Entity e ) const { return m_velocities.at( e ); }

template<> inline
const DirectionComponent& World::GetComponent( Entity e ) const { return m_directions.at( e ); }

template<> inline
const CarTag& World::GetComponent( Entity e ) const { return m_cars.at( e ); }

template<> inline
const CarState& World::GetComponent( Entity e ) const { return m_carStates.at( e ); }

template<> inline
const TrafficLight& World::GetComponent( Entity e ) const { return m_lights.at( e ); }

template<> inline
const TrafficLightController& World::GetComponent( Entity e ) const { return m_lightControllers.at( e ); }

template<> inline
const Drawable& World::GetComponent( Entity e ) const { return m_drawables.at( e ); }