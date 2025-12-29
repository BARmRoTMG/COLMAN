#include "Simulator.h"
#include <iostream>
#include <chrono>
#include <cmath>

using namespace std;

using Clock = std::chrono::steady_clock;

int main()
{
    Simulator sim;
    World& world = sim.GetData();
    float seconds = 0.f;

    //1- state after 3 seconds
    Clock::time_point lastTime = Clock::now();
    while( seconds < 3.0 )
    {
        Clock::time_point currentTime = Clock::now();
        std::chrono::duration<float> delta = currentTime - lastTime;
        lastTime = currentTime;
        seconds += delta.count();

        sim.Update( delta.count() );
    }

    //1.1 check light controller
    auto tlc = world.View<TrafficLightController>();
    if( tlc.size() != 1 )
        cout << "error test 1.1 (-5)" << endl;
    else
    {
        const auto& ctrl = world.GetComponent<TrafficLightController>( tlc[0] );
        if( ctrl.current != Direction::North || round( ctrl.timer ) != 3.f )
            cout << "error test 1.1 (-5)" << endl;
    }

    //1.2 check lights
    auto tl = world.View<TrafficLight>();
    if( tl.size() != 4 )
        cout << "error test 1.2 (-20)" << endl;
    else
    {
        for( auto l : tl )
        {
            auto& t = world.GetComponent<TrafficLight>( l );
            if( t.lane == Direction::North )
            {
                if( !t.green )
                    cout << "error test 1.2 (-5)" << endl;
            }
            else if( t.green )
                cout << "error test 1.2 (-5)" << endl;
        }
    }

    //1.3 check cars
    auto cars = world.View<CarTag>();
    if( cars.size() != 8 )
        cout << "error test 1.3 (-75)" << endl;
    else
    {
        for( auto& c : cars )
        {
            auto& state = world.GetComponent<CarState>( c );
            auto& pos = world.GetComponent<Position>( c );

            if( c == 6 && ( state.crossing || state.waitTime != 0.f || round( pos.y ) < 550.f ) )
                cout << "error test 2.3 (-6)" << endl;

            if( c == 7 && ( state.crossing || round( state.waitTime ) != 3.f || round( pos.x ) != 100.f ) )
                cout << "error test 2.3 (-6)" << endl;

            if( c == 8 && ( state.crossing || round( state.waitTime ) != 3.f || round( pos.y ) != 100.f ) )
                cout << "error test 2.3 (-6)" << endl;

            if( c == 9 && ( state.crossing || round( state.waitTime ) != 3.f || round( pos.x ) != 700.f ) )
                cout << "error test 2.3 (-6)" << endl;

            if( c == 10 && ( state.crossing || round( state.waitTime ) != 0.f || round( pos.y ) != 600.f ) )
                cout << "error test 2.3 (-6)" << endl;

            if( c == 11 && ( state.crossing || round( state.waitTime ) != 3.f || round( pos.x ) != 50.f ) )
                cout << "error test 2.3 (-6)" << endl;

            if( c == 12 && ( state.crossing || round( state.waitTime ) != 3.f || round( pos.y ) != 50.f ) )
                cout << "error test 2.3 (-6)" << endl;

            if( c == 13 && ( state.crossing || round( state.waitTime ) != 3.f || round( pos.x ) != 750.f ) )
                cout << "error test 2.3 (-6)" << endl;
        }
    }

    //next will check after 3 seconds more (total 6)
    //next will check after 10 seconds more (total 16)
    //next will check after 10 seconds more (total 26)

    cout << "done" << endl;

    return 0;
}