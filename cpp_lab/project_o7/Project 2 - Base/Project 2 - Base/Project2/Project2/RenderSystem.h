#pragma once
#include "World.h"

class RenderSystem
{
public:
	void Update( World& world, sf::RenderWindow& window )
	{
		for( Entity e : world.View<Position, Drawable>() )
		{
			auto& p = world.GetComponent<Position>( e );
			auto& d = world.GetComponent<Drawable>( e );

			if( world.HasComponent<TrafficLight>( e ) )
			{
				auto& t = world.GetComponent<TrafficLight>( e );

				sf::CircleShape c( d.size.x );
				c.setFillColor( t.green ? sf::Color::Green : sf::Color::Red );
				c.setPosition( p.value );
				window.draw( c );
			}
			else
			{
				sf::RectangleShape r( d.size );
				r.setFillColor( d.color );
				r.setPosition( p.value );
				window.draw( r );
			}
		}
	}
};