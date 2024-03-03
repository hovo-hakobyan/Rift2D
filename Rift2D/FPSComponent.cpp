#include "FPSComponent.h"
#include "GameObject.h"
#include "TimeManager.h"
#include "TextComponent.h"
#include <format>
#include "ResourceManager.h"
#include "Scene.h"
#include "SceneManager.h"

rift2d::FPSComponent::FPSComponent(GameObject* owner) :
	BaseComponent(owner)
{

}

void rift2d::FPSComponent::init()
{
	
	if (auto owner = getOwner())
	{
		m_pText= owner->getComponent<TextComponent>();
		if (!m_pText)
		{
			auto font = rift2d::ResourceManager::GetInstance().loadFont("Lingua.otf", 36);
			m_pText = getOwner()->addComponent<TextComponent>("FPS",font);
			m_pText->setPosition(10, 10);
		}
		m_pText->registerWatcher(this);
	}
}

void rift2d::FPSComponent::update()
{
	if (!m_pText)
	{
		return;
	}
	

	m_accumulatedSeconds += TimeManager::GetInstance().getDeltaTime();
	++m_frameCount;

	if (m_accumulatedSeconds < m_updateInterval)
	{
		return;
	}


	auto textComp = m_pText;
	textComp->setText(std::format("FPS: {:.1f}", m_frameCount / m_accumulatedSeconds));
	m_frameCount = 0;
	m_accumulatedSeconds = 0;

}

void rift2d::FPSComponent::end()
{
	if (m_pText)
	{
		m_pText->unregisterWatcher(this);
		m_pText = nullptr;
	}
	
}

void rift2d::FPSComponent::onComponentRemoved(BaseComponent* component)
{
	if (component == static_cast<BaseComponent*>(m_pText))
	{
		m_pText = nullptr;
	}
}