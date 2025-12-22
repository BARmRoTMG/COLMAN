#include "EntityFactory.h"
#include "PositionComponent.h"
#include "VelocityComponent.h"
#include "DrawableComponent.h"
#include "AIComponent.h"
#include "AvoidPlayer.h"
#include "UpDown.h"

//------------------------------------------------------------------------------------------------//
EntityFactory::EntityFactory()
{
}
//------------------------------------------------------------------------------------------------//
Entity* EntityFactory::Create( const std::string& type )
{
    Entity* e = nullptr;

    if (type == "player")
    {
        e = new Entity("player");
        e->addComponent<PositionComponent>(200.f, 200.f);
        e->addComponent<VelocityComponent>(10.f, -10.f, 100.f);
        e->addComponent<DrawableComponent>(40.f);
    }
    else if (type == "enemy_avoid")
    {
        e = new Entity("enemy_avoid");
        e->addComponent<PositionComponent>(400.f, 100.f);
        e->addComponent<VelocityComponent>(0.f, 0.f, 40.f);
        e->addComponent<DrawableComponent>(40.f);
        e->addComponent<AIComponent>(AIComponent::BehaviorType::Avoid, std::make_unique<AvoidPlayer>("player"));
    }
    else if (type == "enemy_upDown")
    {
        e = new Entity("enemy_upDown");
        e->addComponent<PositionComponent>(400.f, 100.f);
        e->addComponent<VelocityComponent>(0.f, 0.f, 40.f);
        e->addComponent<DrawableComponent>(40.f);
        e->addComponent<AIComponent>(AIComponent::BehaviorType::UpDown, std::make_unique<UpDown>());
    }

    return e;
}
//------------------------------------------------------------------------------------------------//