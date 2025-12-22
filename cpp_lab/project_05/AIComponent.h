#pragma once
#include "Component.h"
#include "IAiBehavior.h"

struct AIComponent : Component
{
	enum class BehaviorType { Avoid, UpDown };

	AIComponent( BehaviorType t, std::unique_ptr<IAiBehavior> b )
		: m_type( t ), m_behavior( std::move( b ) )
	{
	}

	BehaviorType m_type;
	std::unique_ptr<IAiBehavior> m_behavior;
};