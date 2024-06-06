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
#include "Physics.h"
#include "RiftUI.h"
#include "SceneManager.h"
#include "Components/EnemyManager.h"
#include "Components/HealthDisplayComponent.h"
#include "Components/HealthComponent.h"
#include "Prefabs/DiggerPrefab.h"
#include "Prefabs/DiggerUI.h"


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

	gameObject = std::make_unique<rift2d::GameObject>(this);
	auto enemyManager = gameObject->addComponent<EnemyManager>(3, 4.f);
	addGameObject(std::move(gameObject));

	//UI
	m_pUI = addGameObjectFromPrefab<DiggerUI>();

	if (auto health = m_pPlayer->getComponent<HealthComponent>())
	{
		if (auto healthDisplay = m_pUI->getComponent<HealthDisplayComponent>())
		{
			healthDisplay->setHealthComponent(health);
		}

		health->damageTakenEvent()->subscribe([enemyManager](int)
			{
				enemyManager->reset();
			});

		health->onDeathEvent()->subscribe([this]()
			{
				this->handleGameOver();
			});
		
	}

	
}

void digger::GameScene::onActivate()
{
	rift2d::InputManager::GetInstance().enableInput();
	rift2d::Physics::GetInstance().enable();
}


void digger::GameScene::end()
{
	rift2d::WorldBuilderPrefabRegistry::GetInstance().unregisterPrefabCreators();

}

void digger::GameScene::handleGameOver()
{

	rift2d::SceneManager::GetInstance().setActiveScene("MenuScene", true);
}
