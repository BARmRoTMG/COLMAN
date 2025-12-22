#pragma once

#include "Component.h"

struct PositionComponent : public Component
{
    PositionComponent( float x = 0, float y = 0 ) : m_x( x ), m_y( y ) {}

    float m_x;
    float m_y;
};