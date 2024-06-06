#include "HealthComponent.h"
#include <algorithm>
#include "GameObject.h"
#include "Subject.h"

digger::HealthComponent::HealthComponent(rift2d::GameObject* owner, int maxHealth):
BaseComponent(owner),m_maxHealth(maxHealth),m_currentHealth(maxHealth),m_pOnHealthChanged(std::make_unique<rift2d::Subject<int>>()), m_pOnDamageTaken(std::make_unique<rift2d::Subject<int>>())
{
}



void digger::HealthComponent::init()
{
	BaseComponent::init();
}

void digger::HealthComponent::end()
{
	BaseComponent::end();
	m_pOnHealthChanged->clearSubscribers();
}

void digger::HealthComponent::modify(int amount)
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
	if (amount < 0) m_pOnDamageTaken->notify(m_currentHealth);
}
