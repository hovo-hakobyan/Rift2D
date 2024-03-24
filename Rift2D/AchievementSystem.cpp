#include "AchievementSystem.h"

rift2d::AchievementSystem::AchievementSystem()
{
	std::vector<Achievement> achievements
	{
		Achievement{static_cast<int>(Achievements::ACH_WIN_ONE_GAME), "ACH_WIN_ONE_GAME"}
	};

	m_pSteamAchievements = std::make_unique<SteamAchievements>(achievements);
}

void rift2d::AchievementSystem::onScoreChange(int newScore)
{
	if (newScore == m_scoreToWin)
	{
		m_pSteamAchievements->setAchievement(static_cast<int>(Achievements::ACH_WIN_ONE_GAME));
	}
}

void rift2d::AchievementSystem::subscribeToScoreChanges(Subject<int>* scoreSubject)
{
	scoreSubject->subscribe([this](int newScore)
		{
			this->onScoreChange(newScore);
		});
}
