#include <SFML/Graphics.hpp>

int main()
{
    sf::RenderWindow window( sf::VideoMode( 800, 600 ), "SFML Basics - Week 1" );

    sf::CircleShape player( 40.f );
    player.setFillColor( sf::Color::Green );
    player.setPosition( 100.f, 100.f );

    sf::Clock clock;
    float dt;
    float speed = 200.f;

    while( window.isOpen() )
    {
        // --- Event handling ---
        sf::Event event;
        while( window.pollEvent( event ) )
        {
            if( event.type == sf::Event::Closed )
                window.close();
        }

        // --- Update ---
        dt = clock.restart().asSeconds();
        speed = 200.f;
        if( sf::Keyboard::isKeyPressed( sf::Keyboard::Right ) )
            player.move( speed * dt, 0 );

        // --- Render ---
        window.clear( sf::Color::Black );
        window.draw( player );
        window.display();
    }

    return 0;
}