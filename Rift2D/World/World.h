#pragma once
#include <vector>

#include "Singleton.h"

namespace rift2d
{
	class GameObject;
	class World : public Singleton<World>
	{
		friend class Rift2DEngine;
	public:
		~World() override = default;

		void registerPlayer(GameObject* player);
		void clearPlayers();


		GameObject* getPlayer() const;
		std::vector<GameObject*> getPlayers() const;
		float getDeltaTime() const { return m_deltaTime; }
		float getFixedTime() const { return m_fixedTime; }
		bool isPlayer(GameObject* pObject) const;

	private:
		std::vector<GameObject*> m_players;

		float m_deltaTime = 0.0f;
		float m_fixedTime = 0.01666666667f;

		friend Singleton;
		World() = default;
	};


}
