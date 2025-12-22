#include "Game.h"
#include "PositionComponent.h"
#include <iostream>
using namespace std;

int main()
{
    Game game;
    game.InitStates();

    if (game.m_stateMachine.currentName() != "menu")
        cout << "error initial state (-8)" << endl;

    game.RunUpdate(2.5f);

    if (game.m_stateMachine.currentName() != "menu")
        cout << "error state after 2.5sec (-8)" << endl;

    game.RunEvent("space");

    if (game.m_stateMachine.currentName() != "menu")
        cout << "error state after space (-8)" << endl;

    game.RunEvent("enter");

    if (game.m_stateMachine.currentName() != "play")
        cout << "error state after enter (-8)" << endl;

    game.RunUpdate(2.5f);

    if (game.m_stateMachine.currentName() != "play")
        cout << "error state after 2.5sec (-8)" << endl;

    // ADD THESE DEBUG LINES:
    std::vector<Entity*>& ent5 = game.m_stateMachine.currentState()->m_entities;
    for (auto e : ent5)
    {
        if (e->m_name == "player")
        {
            cout << "DEBUG: Player after 5s: (" << e->getComponent<PositionComponent>()->m_x
                << ", " << e->getComponent<PositionComponent>()->m_y << ")" << endl;
        }
        if (e->m_name == "enemy_avoid")
        {
            cout << "DEBUG: Enemy_avoid after 5s: (" << e->getComponent<PositionComponent>()->m_x
                << ", " << e->getComponent<PositionComponent>()->m_y << ")" << endl;
        }
        if (e->m_name == "enemy_upDown")
        {
            cout << "DEBUG: Enemy_upDown after 5s: (" << e->getComponent<PositionComponent>()->m_x
                << ", " << e->getComponent<PositionComponent>()->m_y << ")" << endl;
        }
    }

    std::vector<Entity*>& ent = game.m_stateMachine.currentState()->m_entities;
    bool foundPlayer = false;
    bool foundEnemy1 = false;
    bool foundEnemy2 = false;

    for (auto e : ent)
    {
        if (e->m_name == "player")
        {
            foundPlayer = true;
            if (e->getComponent<PositionComponent>()->m_x != 225.f || e->getComponent<PositionComponent>()->m_y != 175.f)
                cout << "error player pos after 2.5sec (-8)" << endl;
        }

        if (e->m_name == "enemy_avoid")
        {
            foundEnemy1 = true;
            if (e->getComponent<PositionComponent>()->m_x != 500.f || e->getComponent<PositionComponent>()->m_y != 0.f)
                cout << "error enemy_avoid pos after 2.5sec (-8)" << endl;
        }

        if (e->m_name == "enemy_upDown")
        {
            foundEnemy2 = true;
            if (e->getComponent<PositionComponent>()->m_x != 400.f || e->getComponent<PositionComponent>()->m_y != 200.f)
                cout << "error enemy_upDown pos after 2.5sec (-8)" << endl;
        }

        if (e->m_name == "enemy_avoid")
        {
            foundEnemy1 = true;
            cout << "Actual enemy_avoid pos: (" << e->getComponent<PositionComponent>()->m_x
                << ", " << e->getComponent<PositionComponent>()->m_y << ")" << endl;
            if (e->getComponent<PositionComponent>()->m_x != 500.f || e->getComponent<PositionComponent>()->m_y != 0.f)
                cout << "error enemy_avoid pos after 2.5sec (-8)" << endl;
        }
    }

    if (!foundPlayer || !foundEnemy1 || !foundEnemy2)
        cout << "error in entities creation (-8)" << endl;

    game.RunEvent("space");

    if (game.m_stateMachine.currentName() != "pause")
        cout << "error state after space (-8)" << endl;

    game.RunEvent("space");

    if (game.m_stateMachine.currentName() != "play")
        cout << "error state after second space (-8)" << endl;

    game.RunEvent("escape");

    if (game.m_stateMachine.currentName() != "menu")
        cout << "error state after escape (-8)" << endl;

    cout << "done" << endl;

    return 0;
}