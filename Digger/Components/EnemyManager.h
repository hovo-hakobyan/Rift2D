#pragma once

#include <vector>

#include "BaseComponent.h"
#include "Subject.h"


namespace rift2d
{
	class GameObject;
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

		rift2d::Subject<rift2d::GameObject*>* onEnemySpawn() const { return m_pOnEnemySpawn.get(); }

		void reset();
	private:
		int m_maxAliveEnemies{};
		int m_aliveEnemies{};
		float m_spawnInterval{};
		float m_currentSpawnTime{};

		rift2d::Scene* m_pScene{};

		std::vector<rift2d::GameObject*> m_pEnemies{};

		std::unique_ptr<rift2d::Subject<rift2d::GameObject*>> m_pOnEnemySpawn;
		
	};


}
