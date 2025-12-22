#pragma once

#include "Component.h"

struct VelocityComponent : public Component
{
    VelocityComponent( float vx = 0, float vy = 0, float speed = 0 ) : m_vx( vx ), m_vy( vy ), m_speed( speed ) {}

    float m_vx;
    float m_vy;
    float m_speed;
};