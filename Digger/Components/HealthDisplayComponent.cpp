#include "HealthDisplayComponent.h"
#include "HealthComponent.h"
#include "GameObject.h"
#include "SpriteComponent.h"
#include "ResourceManager.h"

digger::HealthDisplayComponent::HealthDisplayComponent(rift2d::GameObject* owner,HealthComponent* healthComponent):
BaseComponent(owner),m_pHealth(healthComponent)
{
}

void digger::HealthDisplayComponent::init()
{
	BaseComponent::init();
	initInternal();
	
}

void digger::HealthDisplayComponent::end()
{
	BaseComponent::end();
	if(m_pHealth) m_pHealth->healthChangedEvent()->unsubscribe(m_observerId);
	
}

void digger::HealthDisplayComponent::onComponentRemoved(BaseComponent* component)
{
	if (component == static_cast<BaseComponent*>(m_pHealth))
	{
		m_pHealth = nullptr;
	}
}

void digger::HealthDisplayComponent::setHealthComponent(HealthComponent* healthComponent)
{
	m_pHealth = healthComponent;
	initInternal();
}

void digger::HealthDisplayComponent::updateLivesDisplay(int currentLives)
{
	if (!m_pHealth) return;

	auto setRender = [](rift2d::SpriteComponent* component, bool shouldRend)
		{
			component->shouldRender(shouldRend);
		};
	const size_t count = std::min(static_cast<size_t>(currentLives), m_pSpriteComponents.size());

	std::for_each_n(m_pSpriteComponents.begin(), count, [&setRender](rift2d::SpriteComponent* component)
		{
			setRender(component, true);
		});

	if (count < m_pSpriteComponents.size())
	{
		std::for_each(m_pSpriteComponents.begin() + count, m_pSpriteComponents.end(), [&setRender](rift2d::SpriteComponent* component)
			{
				setRender(component, false);
			});
	}
}

void digger::HealthDisplayComponent::initInternal()
{
	if (m_pHealth)
	{
		m_pHealth->registerWatcher(this);
		m_pSpriteComponents.reserve(m_pHealth->getMaxHealth());
		float offset = 0;
		for (int i = 0; i < m_pHealth->getMaxHealth(); ++i)
		{
			if (auto spComp = getOwner()->addComponent<rift2d::SpriteComponent>(true))
			{
				if (const auto texture = rift2d::ResourceManager::GetInstance().loadTexture("health.png"))
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
