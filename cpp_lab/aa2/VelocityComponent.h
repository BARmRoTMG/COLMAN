#pragma once
#include "Component.h"

struct VelocityComponent : Component
{
    VelocityComponent( int vx, int vy ) : m_vx( vx ), m_vy( vy ) {}

    int m_vx;
    int m_vy;
};