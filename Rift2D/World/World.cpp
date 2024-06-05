#include "World.h"

namespace rift2d
{
	void World::registerPlayer(GameObject* player)
	{
		m_players.push_back(player);
	}

	void World::clearPlayers()
	{
		m_players.clear();
	}

	GameObject* World::getPlayer() const
	{
		return m_players.front();
	}

	std::vector<GameObject*> World::getPlayers() const
	{
		return m_players;
	}

	bool World::isPlayer(GameObject* pObject) const
	{
		auto player = std::ranges::find(m_players, pObject);
		if (player == m_players.end()) return false;
		return true;
	}
}
