#include "ScoreComponent.h"

digger::ScoreComponent::ScoreComponent(rift2d::GameObject* owner):
BaseComponent(owner),m_pOnScoreChange(std::make_unique<rift2d::Subject<int>>())
{
}

void digger::ScoreComponent::init()
{
	BaseComponent::init();
}

void digger::ScoreComponent::end()
{
	BaseComponent::end();
	m_pOnScoreChange->clearSubscribers();
}

void digger::ScoreComponent::modify(int amount)
{
	m_currentScore += amount;
	m_currentScore = std::max(m_currentScore, 0);
	m_pOnScoreChange->notify(m_currentScore);
}
