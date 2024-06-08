#include "ScoreDisplayComponent.h"
#include "GameObject.h"
#include "ResourceManager.h"
#include "ScoreComponent.h"
#include "TextComponent.h"

digger::ScoreDisplayComponent::ScoreDisplayComponent(rift2d::GameObject* owner, ScoreComponent* pScoreComponent):
BaseComponent(owner),m_pScoreComponent(pScoreComponent)
{
}

void digger::ScoreDisplayComponent::onComponentRemoved(BaseComponent* component)
{
	if (component == m_pScoreComponent)
	{
		m_pScoreComponent->scoreChangeEvent()->unsubscribe(m_observerID);
		m_pScoreComponent = nullptr;
	}

	if (component ==m_pTextComponent)
	{
		m_pTextComponent = nullptr;
	}
}

void digger::ScoreDisplayComponent::init()
{
	BaseComponent::init();

	if (m_pScoreComponent)
	{
		m_pScoreComponent->registerWatcher(this);

		m_observerID = m_pScoreComponent->scoreChangeEvent()->subscribe([this](int newScore)
			{
				this->updateScore(newScore);
			});
	}

	auto font = rift2d::ResourceManager::GetInstance().loadFont("Lingua.otf", 16);
	m_pTextComponent = getOwner()->addComponent<rift2d::TextComponent>("Score: 0" , font);
	m_pTextComponent->registerWatcher(this);
}

void digger::ScoreDisplayComponent::end()
{
	BaseComponent::end();
	if (m_pScoreComponent) m_pScoreComponent->scoreChangeEvent()->unsubscribe(m_observerID);
}

void digger::ScoreDisplayComponent::updateScore(int currentScore) const
{
	if(m_pTextComponent)
	{
		m_pTextComponent->setText(std::format("Score: {}", currentScore));
	}
}
