#include "ScoreComponent.h"

#include "AchievementSystem.h"

rift2d::ScoreComponent::ScoreComponent(GameObject* owner):
BaseComponent(owner),m_pOnScoreChange(std::make_unique<Subject<int>>())
{
}

void rift2d::ScoreComponent::init()
{
	BaseComponent::init();
	AchievementSystem::GetInstance().subscribeToScoreChanges(m_pOnScoreChange.get());
}

void rift2d::ScoreComponent::end()
{
	m_pOnScoreChange->clearSubscribers();
}

void rift2d::ScoreComponent::modify(int amount)
{
	m_currentScore += amount;
	m_currentScore = std::max(m_currentScore, 0);
	m_pOnScoreChange->notify(m_currentScore);
}
