#pragma once

#include <SFML/Graphics.hpp>
#include "CarDispatcher.h"
#include "TrafficLight.h"

class Simulator
{
public:
    Simulator();
	~Simulator();

public:
	void Run();

private:
    void handleEvents();
    void update( float dt );
    void render();

private:
    sf::RenderWindow        m_window;
    CarDispatcher           m_dispatcher;

private:
    LightState              m_light = LightState::NS_Green;
    float                   m_lightTimer = 0.f;
};
