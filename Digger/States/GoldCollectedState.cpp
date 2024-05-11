#include "GoldCollectedState.h"

#include "GameObject.h"

void digger::GoldCollectedState::onEnter(rift2d::GameObject* gameObject)
{
	gameObject->markForDestroy();
	//Score will be added here as well
}

void digger::GoldCollectedState::update(rift2d::GameObject* /*gameObject*/)
{
}

void digger::GoldCollectedState::onExit(rift2d::GameObject* /*gameObject*/)
{
}
