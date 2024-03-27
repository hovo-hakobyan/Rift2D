#pragma once
#include <vector>
#include "Subject.h"

namespace rift2d
{
	struct Achievement
	{
		Achievement(int id, const char* name)
			:achievementID(id),
			chAchievementID(name){}
	

		int achievementID{};
		const char* chAchievementID{};
		char name[128]{};
		char description[256]{};
		bool achieved{};
		int iconImage{};
	};

	class SteamAchievements final
	{
	public:
		SteamAchievements( std::vector<Achievement> achievements);
		~SteamAchievements()= default;
		SteamAchievements(const SteamAchievements& other) = delete;
		SteamAchievements(SteamAchievements&& other) = delete;
		SteamAchievements& operator=(const SteamAchievements& other) = delete;
		SteamAchievements& operator=(SteamAchievements&& other) = delete;

		bool setAchievement(int ID);
	private:
		std::vector<Achievement> m_achievements;
	};


}
