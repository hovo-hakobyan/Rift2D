#include "ScoreDisplayComponent.h"

#include "GameObject.h"
#include "ResourceManager.h"
#include "ScoreComponent.h"
#include "TextComponent.h"

rift2d::ScoreDisplayComponent::ScoreDisplayComponent(GameObject* owner, ScoreComponent* pScoreComponent):
BaseComponent(owner),m_pScoreComponent(pScoreComponent)
{
}

void rift2d::ScoreDisplayComponent::onComponentRemoved(BaseComponent* component)
{
	if (component == m_pScoreComponent)
	{
		m_pScoreComponent = nullptr;
	}

	if (component ==m_pTextComponent)
	{
		m_pTextComponent = nullptr;
	}
}

void rift2d::ScoreDisplayComponent::init()
{
	BaseComponent::init();

	if (m_pScoreComponent)
	{
		m_pScoreComponent->registerWatcher(this);

		m_observerID = m_pScoreComponent->onScoreChangeEvent()->subscribe([this](int newScore)
			{
				this->updateScore(newScore);
			});
	}

	auto font = rift2d::ResourceManager::GetInstance().loadFont("Lingua.otf", 16);
	m_pTextComponent = getOwner()->addComponent<TextComponent>("Score: 0" , font);
	m_pTextComponent->registerWatcher(this);
}

void rift2d::ScoreDisplayComponent::end()
{
	m_pScoreComponent->onScoreChangeEvent()->unsubscribe(m_observerID);
}

void rift2d::ScoreDisplayComponent::updateScore(int currentScore) const
{
	if(m_pTextComponent)
	{
		m_pTextComponent->setText(std::format("Score: {}", currentScore));
	}
}
