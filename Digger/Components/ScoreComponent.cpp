#include "ScoreComponent.h"

#include "GameModeManager.h"
#include "Digger/DiggerGameMode.h"

digger::ScoreComponent::ScoreComponent(rift2d::GameObject* owner):
BaseComponent(owner), m_pOnScoreChange(std::make_unique<rift2d::Subject<int>>())
{
}

void digger::ScoreComponent::init()
{
	BaseComponent::init();
}

void digger::ScoreComponent::end()
{
	BaseComponent::end();
	if(auto gameMode = dynamic_cast<DiggerGameMode*>( rift2d::GameModeManager::GetInstance().getGameMode()))
	{
		gameMode->addScore(m_currentScore);
	}
}

void digger::ScoreComponent::modify(int amount)
{
	m_currentScore += amount;
	m_currentScore = std::max(m_currentScore, 0);
	m_pOnScoreChange->notify(m_currentScore);

}
