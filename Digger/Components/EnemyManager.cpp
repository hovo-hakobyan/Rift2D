#include "EnemyManager.h"

#include "SceneManager.h"
#include "World.h"
#include "Prefabs/Enemy.h"
#include "Scene.h"	

digger::EnemyManager::EnemyManager(rift2d::GameObject* owner, int maxAliveEnemies, float spawnInterval):
BaseComponent(owner),m_maxAliveEnemies(maxAliveEnemies),m_spawnInterval(spawnInterval)
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

		
		m_pScene->addGameObjectFromPrefab<Enemy>();
	}

}
