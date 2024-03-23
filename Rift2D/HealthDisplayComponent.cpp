#include "HealthDisplayComponent.h"
#include "HealthComponent.h"
#include "GameObject.h"
#include "SpriteComponent.h"
#include "ResourceManager.h"

rift2d::HealthDisplayComponent::HealthDisplayComponent(GameObject* owner,HealthComponent* healthComponent):
BaseComponent(owner),m_pHealth(healthComponent)
{
}

void rift2d::HealthDisplayComponent::init()
{
	BaseComponent::init();
	if(m_pHealth)
	{
		m_pHealth->registerWatcher(this);
		m_pSpriteComponents.reserve(m_pHealth->getMaxHealth());
		float offset = 0;
		for (int i = 0; i < m_pHealth->getMaxHealth(); ++i)
		{
			if (auto spComp = getOwner()->addComponent<SpriteComponent>())
			{
				if (const auto texture = ResourceManager::GetInstance().loadTexture("health.png"))
				{
					constexpr float step = 25.f;
					spComp->setTexture(texture, { offset,0 });
					offset += step;
					m_pSpriteComponents.push_back(spComp);
				}
			}
		}

		m_observerId = m_pHealth->healthChangedEvent()->subscribe([this](int newHealth)
			{
				this->updateLivesDisplay(newHealth);
			});
	}
	
}

void rift2d::HealthDisplayComponent::end()
{
	if(m_pHealth) m_pHealth->healthChangedEvent()->unsubscribe(m_observerId);
	
}

void rift2d::HealthDisplayComponent::onComponentRemoved(BaseComponent* component)
{
	if (component == static_cast<BaseComponent*>(m_pHealth))
	{
		m_pHealth = nullptr;
	}
}

void rift2d::HealthDisplayComponent::updateLivesDisplay(int currentLives)
{
	if (!m_pHealth) return;

	auto setRender = [](SpriteComponent* component, bool shouldRend)
		{
			component->shouldRender(shouldRend);
		};
	const size_t count = std::min(static_cast<size_t>(currentLives), m_pSpriteComponents.size());

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
