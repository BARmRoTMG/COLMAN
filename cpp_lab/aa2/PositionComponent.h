#pragma once
#include "Component.h"

struct PositionComponent : Component
{
    PositionComponent( int x, int y ) : m_x( x ), m_y( y ) {}

    int m_x;
    int m_y;
};