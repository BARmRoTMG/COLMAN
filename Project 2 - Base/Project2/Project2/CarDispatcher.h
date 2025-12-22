#pragma once
#include <queue>
#include <vector>
#include "Car.h"
#include "TrafficLight.h"

class CarDispatcher
{
public:
    void AddCar( const Car& car );
    void Update( float dt, LightState light );

public: // For rendering
    std::vector<Car> GetWaitingCars() const;

private:
    std::queue<Car> m_queues[4];
};
