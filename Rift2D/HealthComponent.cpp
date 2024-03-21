#include "HealthComponent.h"

#include <algorithm>

#include "GameObject.h"
#include "ResourceManager.h"
#include "SpriteComponent.h"

rift2d::HealthComponent::HealthComponent(GameObject* owner, int maxHealth):
BaseComponent(owner),m_maxHealth(maxHealth),m_currentHealth(maxHealth),m_pHealthChanged(std::make_unique<Subject<int>>())
{
}



void rift2d::HealthComponent::init()
{
	BaseComponent::init();
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
	if(m_currentHealth > m_maxHealth)
	{
		m_currentHealth = m_maxHealth;
	}

	m_pHealthChanged->notify(m_currentHealth);
}

void rift2d::HealthComponent::onHealthChanged(const std::function<void(int)>& callback) const
{
	m_pHealthChanged->subscribe(callback);
}
