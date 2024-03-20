#include "HealthComponent.h"

#include <algorithm>

#include "GameObject.h"
#include "ResourceManager.h"
#include "SpriteComponent.h"

rift2d::HealthComponent::HealthComponent(GameObject* owner, int maxHealth, bool shouldRender):
BaseComponent(owner),m_maxHealth(maxHealth),m_currentHealth(maxHealth),m_shouldRender(shouldRender)
{
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

	updateRendering();
}

void rift2d::HealthComponent::init()
{
	BaseComponent::init();

	if (m_shouldRender)
	{
		m_pSpriteComponents.reserve(m_maxHealth);
		float offset = 0;
		for (int i = 0; i <m_maxHealth ; ++i)
		{
			if(auto spComp = getOwner()->addComponent<SpriteComponent>())
			{
				if(auto texture = ResourceManager::GetInstance().loadTexture("health.png"))
				{
					constexpr float step = 25.f;
					spComp->setTexture(texture, { offset,0 });
					offset += step;
					m_pSpriteComponents.push_back(spComp);
				}
			}
		}
	}
	
}

void rift2d::HealthComponent::updateRendering()
{
	auto setRender = [](SpriteComponent* component, bool shouldRend)
	{
		component->shouldRender(shouldRend);
	};
	size_t count = std::min(static_cast<size_t>(m_currentHealth), m_pSpriteComponents.size());

	std::for_each_n(m_pSpriteComponents.begin(), count, [&setRender](SpriteComponent* component)
		{
			setRender(component, true);
		});

	if (count < m_pSpriteComponents.size())
	{
		std::for_each(m_pSpriteComponents.begin() + count, m_pSpriteComponents.end(), [&setRender](SpriteComponent* component)
			{
				setRender(component, false);
			});
	}
}


