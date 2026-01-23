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
    while (seconds < 3.0)
    {
        Clock::time_point currentTime = Clock::now();
        std::chrono::duration<float> delta = currentTime - lastTime;
        lastTime = currentTime;
        seconds += delta.count();

        sim.Update(delta.count());
    }

    cout << "=== After 3 seconds ===" << endl;
    cout << "Total time: " << seconds << endl << endl;

    //1.1 check light controller
    auto tlc = world.View<TrafficLightController>();
    if (tlc.size() != 1)
        cout << "error test 1.1 (-5)" << endl;
    else
    {
        const auto& ctrl = world.GetComponent<TrafficLightController>(tlc[0]);
        cout << "Controller - current: " << (int)ctrl.current << " (should be 0=North), timer: " << ctrl.timer << " (should be ~3)" << endl;
        if (ctrl.current != Direction::North || round(ctrl.timer) != 3.f)
            cout << "error test 1.1 (-5)" << endl;
    }
    cout << endl;

    //1.2 check lights
    auto tl = world.View<TrafficLight>();
    if (tl.size() != 4)
        cout << "error test 1.2 (-20)" << endl;
    else
    {
        cout << "Traffic Lights:" << endl;
        for (auto l : tl)
        {
            auto& t = world.GetComponent<TrafficLight>(l);
            cout << "  Light " << l << " - lane: " << (int)t.lane << ", green: " << t.green << endl;
            if (t.lane == Direction::North)
            {
                if (!t.green)
                    cout << "error test 1.2 (-5)" << endl;
            }
            else if (t.green)
                cout << "error test 1.2 (-5)" << endl;
        }
    }
    cout << endl;

    //1.3 check cars
    auto cars = world.View<CarTag>();
    if (cars.size() != 8)
        cout << "error test 1.3 (-75)" << endl;
    else
    {
        cout << "Cars state:" << endl;
        for (auto& c : cars)
        {
            auto& state = world.GetComponent<CarState>(c);
            auto& pos = world.GetComponent<Position>(c);
            auto& dir = world.GetComponent<DirectionComponent>(c);
            auto& vel = world.GetComponent<Velocity>(c);

            cout << "Car " << c << " - Dir:" << (int)dir.value
                << " Pos:(" << pos.x << "," << pos.y << ")"
                << " Vel:(" << vel.valueX << "," << vel.valueY << ")"
                << " crossing:" << state.crossing
                << " waitTime:" << state.waitTime << endl;

            if (c == 6)
            {
                cout << "  Expected: crossing=false, waitTime=0, y>=550" << endl;
                if (state.crossing || state.waitTime != 0.f || round(pos.y) < 550.f)
                    cout << "  ERROR test 2.3 (-6)" << endl;
            }

            if (c == 7)
            {
                cout << "  Expected: crossing=false, waitTime~=3, x=100" << endl;
                if (state.crossing || round(state.waitTime) != 3.f || round(pos.x) != 100.f)
                    cout << "  ERROR test 2.3 (-6)" << endl;
            }

            if (c == 8)
            {
                cout << "  Expected: crossing=false, waitTime~=3, y=100" << endl;
                if (state.crossing || round(state.waitTime) != 3.f || round(pos.y) != 100.f)
                    cout << "  ERROR test 2.3 (-6)" << endl;
            }

            if (c == 9)
            {
                cout << "  Expected: crossing=false, waitTime~=3, x=700" << endl;
                if (state.crossing || round(state.waitTime) != 3.f || round(pos.x) != 700.f)
                    cout << "  ERROR test 2.3 (-6)" << endl;
            }

            if (c == 10)
            {
                cout << "  Expected: crossing=false, waitTime=0, y~=600" << endl;
                if (state.crossing || round(state.waitTime) != 0.f || round(pos.y) != 600.f)
                    cout << "  ERROR test 2.3 (-6)" << endl;
            }

            if (c == 11)
            {
                cout << "  Expected: crossing=false, waitTime~=3, x=50" << endl;
                if (state.crossing || round(state.waitTime) != 3.f || round(pos.x) != 50.f)
                    cout << "  ERROR test 2.3 (-6)" << endl;
            }

            if (c == 12)
            {
                cout << "  Expected: crossing=false, waitTime~=3, y=50" << endl;
                if (state.crossing || round(state.waitTime) != 3.f || round(pos.y) != 50.f)
                    cout << "  ERROR test 2.3 (-6)" << endl;
            }

            if (c == 13)
            {
                cout << "  Expected: crossing=false, waitTime~=3, x=750" << endl;
                if (state.crossing || round(state.waitTime) != 3.f || round(pos.x) != 750.f)
                    cout << "  ERROR test 2.3 (-6)" << endl;
            }
        }
    }

    cout << endl << "done" << endl;

    return 0;
}