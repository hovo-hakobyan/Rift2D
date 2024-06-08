#include "EnemyManager.h"

#include "AIController.h"
#include "SceneManager.h"
#include "World.h"
#include "Prefabs/Enemy.h"
#include "GameObject.h"
#include "Scene.h"	

digger::EnemyManager::EnemyManager(rift2d::GameObject* owner, int maxAliveEnemies, float spawnInterval):
BaseComponent(owner),m_maxAliveEnemies(maxAliveEnemies),m_spawnInterval(spawnInterval),m_currentSpawnTime(spawnInterval),
m_pOnEnemySpawn(std::make_unique<rift2d::Subject<rift2d::GameObject*>>())
{
}


void digger::EnemyManager::init()
{
	BaseComponent::init();

	m_pScene = rift2d::SceneManager::GetInstance().getActiveScene();
}

void digger::EnemyManager::update()
{
	if (m_aliveEnemies >= m_maxAliveEnemies) return;
	m_currentSpawnTime += rift2d::World::GetInstance().getDeltaTime();

	if(m_currentSpawnTime >= m_spawnInterval)
	{
		++m_aliveEnemies;
		m_currentSpawnTime = 0.f;

		const auto enemyPtr = m_pScene->addGameObjectFromPrefab<Enemy>();
		m_pEnemies.push_back(enemyPtr);
		m_pOnEnemySpawn->notify(enemyPtr);
	}

}

void digger::EnemyManager::reset()
{
	for ( auto& pEnemy : m_pEnemies)
	{
		if(auto comp = pEnemy->getComponent<rift2d::AIController>())
		{
			comp->onDeathEvent()->clearSubscribers();
		}
		pEnemy->markForDestroy();
		
	}

	m_aliveEnemies = 0;
	m_currentSpawnTime = 0.f;
}
