#include "GameScene.h"

#include "AIController.h"
#include "Exception.h"
#include "WorldBuilder.h"
#include "Prefabs/DirtPrefab.h"
#include "Prefabs/EmeraldPrefab.h"
#include "Prefabs/MoneyPrefab.h"
#include "FPSComponent.h"
#include "InputManager.h"
#include "Locator.h"
#include "World.h"
#include "Prefabs/DiggerPrefab.h"
#include "Prefabs/Enemy.h"

digger::GameScene::GameScene(int level):
Scene("level" + std::to_string(level)), m_levelIdx(level)
{
}

void digger::GameScene::init()
{
	auto& prefabRegistry = rift2d::WorldBuilderPrefabRegistry::GetInstance();

	//register empty tile
	prefabRegistry.registerPrefabCreator(0, [](const glm::vec3&, Scene*)
		{
			return nullptr;
		});


	prefabRegistry.registerPrefabCreator(1, [](const glm::vec3& loc, Scene* pScene)
		{
			return pScene->addGameObjectFromPrefab<DirtPrefab>(loc);
		});

	prefabRegistry.registerPrefabCreator(2, [](const glm::vec3& loc, Scene* pScene)
		{
			return pScene->addGameObjectFromPrefab<MoneyPrefab>(loc);
		});

	prefabRegistry.registerPrefabCreator(3, [](const glm::vec3& loc, Scene* pScene)
		{
			return pScene->addGameObjectFromPrefab<EmeraldPrefab>(loc);
		});

	try
	{
		rift2d::WorldBuilder::buildLevel("level" + std::to_string(m_levelIdx));
	}
	catch (const rift2d::RiftException& e)
	{
		e.logToFile();
		throw;
	}

	auto gameObject = std::make_unique<rift2d::GameObject>(this);
	gameObject->addComponent<rift2d::FPSComponent>();
	addGameObject(std::move(gameObject));

	m_pPlayer = addGameObjectFromPrefab<DiggerPrefab>();

	//add sound mappings
	auto& ss = rift2d::ServiceLocator::getSoundSystem();
	ss.addSoundMapping(0, "laser.mp3");
	ss.addSoundMapping(1, "laser_explode.mp3");
	ss.addSoundMapping(2, "gold_tick.mp3");

	std::cout << "DPad to move\nX to shoot";

	m_pEnemy= addGameObjectFromPrefab<Enemy>();
	

}

void digger::GameScene::update()
{

	m_currentTime += rift2d::World::GetInstance().getDeltaTime();

	if(m_currentTime >= m_maxTime)
	{
		if(!m_pAIController) m_pAIController = m_pEnemy->getComponent<rift2d::AIController>();

		m_pAIController->moveTo(m_pPlayer);
		m_currentTime = 0.f;
	}
}

void digger::GameScene::end()
{
	rift2d::WorldBuilderPrefabRegistry::GetInstance().unregisterPrefabCreators();

}
