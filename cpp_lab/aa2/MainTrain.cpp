#include <iostream>
#include "MovementSystem.h"
#include "BoundarySystem.h"
#include "ResourceManager.h"

using namespace std;

int main()
{
    //basic movement test
    {
        Entity e1;
        e1.addComponent<PositionComponent>( 0, 0 );
        e1.addComponent<VelocityComponent>( 5, 7 );

        std::vector<Entity*> v1 = { &e1 };

        MovementSystem m1;
        m1.update( v1 );

        auto* pos1 = e1.getComponent<PositionComponent>();

        if( nullptr == pos1 )
            cout << "Error (-40)" << endl;
        else if( pos1->m_x != 5 || pos1->m_y != 7 )
            cout << "Error (-40)" << endl;
    }

    //basic boundary test
    {
        Entity e2;
        e2.addComponent<PositionComponent>( 95, 95 );
        e2.addComponent<VelocityComponent>( 10, 10 );

        std::vector<Entity*> v2 = { &e2 };

		MovementSystem m2;
        m2.update( v2 );
		
        BoundarySystem b2( 0, 100, 0, 100 );
        b2.update( v2 );

        auto* pos2 = e2.getComponent<PositionComponent>();
        auto* vel2 = e2.getComponent<VelocityComponent>();

        if( nullptr == pos2 || nullptr == vel2 )
            cout << "Error (-30)" << endl;
        else if( pos2->m_x != 100 || pos2->m_y != 100 || vel2->m_vx != 0 || vel2->m_vy != 0 )
            cout << "Error (-30)" << endl;
    }

    //basic resource management test
    {
        ResourceManager rm;
        int* a = rm.load( "fileA" );
        int* b = rm.load( "fileA" );

        if( nullptr == a || nullptr == b )
            cout << "Error (-30)" << endl;
        else if( a != b )
            cout << "Error (-30)" << endl;
    }

    cout << "done" << endl;

    return 0;
}