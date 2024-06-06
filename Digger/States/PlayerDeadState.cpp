#include "PlayerDeadState.h"
#include "GameObject.h"
#include "InputManager.h"
#include "Physics.h"
#include "PlayerNormalState.h"
#include "SpriteComponent.h"
#include "StateComponent.h"
#include "World.h"
#include "Components/HealthComponent.h"

void digger::PlayerDeadState::onEnter(rift2d::GameObject* gameObject)
{
	if (const auto sprite = gameObject->getComponent<rift2d::SpriteComponent>())
	{
		sprite->setTexture("grave.png");
	}

	rift2d::InputManager::GetInstance().disableInput();
	rift2d::Physics::GetInstance().disable();
}

void digger::PlayerDeadState::update(rift2d::GameObject* gameObject)
{
	m_currentDeadTime += rift2d::World::GetInstance().getDeltaTime();
	if(m_currentDeadTime >= m_maxDeadTime)
	{
		if(auto stateComp = gameObject->getComponent<rift2d::StateComponent>())
		{
			if(auto health = gameObject->getComponent<HealthComponent>())
			{
				stateComp->changeState(std::make_unique<PlayerNormalState>(health));
			}
			
		}
	}
}

void digger::PlayerDeadState::onExit(rift2d::GameObject*)
{
	rift2d::InputManager::GetInstance().enableInput();
	rift2d::Physics::GetInstance().enable();
}
