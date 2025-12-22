#pragma once

#include "Component.h"

struct DrawableComponent : public Component
{
    DrawableComponent( int size )
    {
        m_size = size;
    }
    
    int m_size;
};