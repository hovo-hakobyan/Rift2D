#include "SteamAchievements.h"
#include <isteamuser.h>
#include <isteamuserstats.h>
#include <isteamutils.h>


rift2d::SteamAchievements::SteamAchievements( std::vector<Achievement> achievements)
{
	m_achievements = std::move(achievements);
}

bool rift2d::SteamAchievements::setAchievement(int ID)
{
	SteamUserStats()->SetAchievement(m_achievements[ID].chAchievementID);
	return SteamUserStats()->StoreStats();

}
