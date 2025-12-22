#pragma once
#include "Component.h"
#include "IAiBehavior.h"

struct AIComponent : Component
{
	AIComponent( std::unique_ptr<IAiBehavior> b )
		: m_behavior( std::move( b ) )
	{
	}

	std::unique_ptr<IAiBehavior> m_behavior;
};