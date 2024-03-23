#include "HealthComponent.h"

#include <algorithm>

#include "GameObject.h"
#include "ResourceManager.h"
#include "SpriteComponent.h"

rift2d::HealthComponent::HealthComponent(GameObject* owner, int maxHealth):
BaseComponent(owner),m_maxHealth(maxHealth),m_currentHealth(maxHealth),m_pOnHealthChanged(std::make_unique<Subject<int>>())
{
}



void rift2d::HealthComponent::init()
{
	BaseComponent::init();
}

void rift2d::HealthComponent::end()
{
	m_pOnHealthChanged->clearSubscribers();
}

void rift2d::HealthComponent::modify(int amount)
{
	if (m_isDead || amount ==0) return;

	m_currentHealth += amount;
	if(m_currentHealth <= 0)
	{
		m_isDead = true;
		m_currentHealth = 0;
	}
	m_currentHealth = std::min(m_currentHealth, m_maxHealth);

	m_pOnHealthChanged->notify(m_currentHealth);
}
