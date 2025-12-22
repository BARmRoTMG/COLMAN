#pragma once
#include "Entity.h"

class EntityFactory
{
public:
    EntityFactory();

    Entity* Create(const std::string& type);
};