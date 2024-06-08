#include "GoldActivateState.h"
#include "GameObject.h"
#include "GoldFallingState.h"
#include "StateComponent.h"
#include "World.h"

void digger::GoldActivateState::update(rift2d::GameObject* gameObject)
{
	m_currentFallTime += rift2d::World::GetInstance().getDeltaTime();
	if(m_currentFallTime >= m_maxFallTime)
	{
		const auto stateComponent = gameObject->getComponent<rift2d::StateComponent>();
		stateComponent->changeState(std::make_unique<GoldFallingState>());
	}
}
