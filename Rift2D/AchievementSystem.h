#pragma once
#include <memory>
#include <Singleton.h>

#include "SteamAchievements.h"
#include "Subject.h"

namespace rift2d
{
	class AchievementSystem final : public Singleton<AchievementSystem>
	{
		friend class Singleton<AchievementSystem>;

		enum class Achievements
		{
			ACH_WIN_ONE_GAME = 0,
		};

		int m_scoreToWin{ 500 };
		std::unique_ptr<SteamAchievements> m_pSteamAchievements;

		AchievementSystem();
		void onScoreChange(int newScore);

	public:
		~AchievementSystem() override = default;

		void subscribeToScoreChanges(Subject<int>* scoreSubject);
	};


}
