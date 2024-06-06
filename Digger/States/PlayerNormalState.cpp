#include "PlayerNormalState.h"
#include "GameObject.h"
#include "InputManager.h"
#include "PlayerDeadState.h"
#include "Transform.h"
#include "SpriteComponent.h"
#include "StateComponent.h"
#include "Components/HealthComponent.h"

digger::PlayerNormalState::PlayerNormalState(HealthComponent* pHealth): m_pHealth(pHealth)
{
}

void digger::PlayerNormalState::onEnter(rift2d::GameObject* gameObject)
{
	if (const auto sprite = gameObject->getComponent<rift2d::SpriteComponent>())
	{
		sprite->setTexture("digger.png");
	}

	gameObject->getTransform()->setLocalPosition(150.f, 390.f);

	m_observerId = m_pHealth->damageTakenEvent()->subscribe([this](int newHealth)
		{
			this->onPlayerHealthChanged(newHealth);
		});

	rift2d::InputManager::GetInstance().enableInput();
}

void digger::PlayerNormalState::update(rift2d::GameObject* gameObject)
{
	if(m_isDead)
	{
		if (auto stateComp = gameObject->getComponent<rift2d::StateComponent>())
		{
			stateComp->changeState(std::make_unique<PlayerDeadState>());
		}
	}
}

void digger::PlayerNormalState::onExit(rift2d::GameObject*)
{
	m_pHealth->damageTakenEvent()->unsubscribe(m_observerId);
}

void digger::PlayerNormalState::onPlayerHealthChanged(int)
{
	m_isDead = true;
}

