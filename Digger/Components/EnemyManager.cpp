#include "EnemyManager.h"

#include "SceneManager.h"
#include "World.h"
#include "Prefabs/Enemy.h"
#include "GameObject.h"
#include "Scene.h"	

digger::EnemyManager::EnemyManager(rift2d::GameObject* owner, int maxAliveEnemies, float spawnInterval):
BaseComponent(owner),m_maxAliveEnemies(maxAliveEnemies),m_spawnInterval(spawnInterval),m_currentSpawnTime(spawnInterval)
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

		m_pEnemies.push_back(m_pScene->addGameObjectFromPrefab<Enemy>());
		
	}

}

void digger::EnemyManager::reset()
{
	for ( auto& pEnemy : m_pEnemies)
	{
		pEnemy->markForDestroy();
	}

	m_aliveEnemies = 0;
	m_currentSpawnTime = 0.f;
}
