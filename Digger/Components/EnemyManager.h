#pragma once

#include "BaseComponent.h"

namespace rift2d
{
	class Scene;
}

namespace digger
{

	class EnemyManager : public rift2d::BaseComponent
	{
	public:
		EnemyManager(rift2d::GameObject* owner, int maxAliveEnemies, float spawnInterval);
		virtual ~EnemyManager() override = default;
		EnemyManager(const EnemyManager& other) = delete;
		EnemyManager(EnemyManager&& other) = delete;
		EnemyManager& operator=(const EnemyManager& other) = delete;
		EnemyManager& operator=(EnemyManager&& other) = delete;

		virtual void init() override;
		virtual void update() override;
	private:
		int m_maxAliveEnemies{};
		int m_aliveEnemies{};
		float m_spawnInterval{};
		float m_currentSpawnTime{};

		rift2d::Scene* m_pScene{};
	};


}
