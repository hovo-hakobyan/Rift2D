#include "GameScene.h"
#include "AIController.h"
#include "Exception.h"
#include "WorldBuilder.h"
#include "Prefabs/DirtPrefab.h"
#include "Prefabs/EmeraldPrefab.h"
#include "Prefabs/MoneyPrefab.h"
#include "GameModeManager.h"
#include "InputManager.h"
#include "Locator.h"
#include "Physics.h"
#include "SceneManager.h"
#include "World.h"
#include "Commands/SkipLevelCommand.h"
#include "Components/EnemyManager.h"
#include "Components/HealthDisplayComponent.h"
#include "Components/HealthComponent.h"
#include "Components/ScoreComponent.h"
#include "Components/ScoreDisplayComponent.h"
#include "Digger/EmeraldManager.h"
#include "Digger/GameSettings.h"
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


	m_pPlayer = addGameObjectFromPrefab<DiggerPrefab>();

	//add sound mappings
	auto& ss = rift2d::ServiceLocator::getSoundSystem();
	ss.addSoundMapping(0, "laser.mp3");
	ss.addSoundMapping(1, "laser_explode.mp3");
	ss.addSoundMapping(2, "gold_tick.mp3");

	std::cout << "DPad to move\nX to shoot";

	auto gameObject = std::make_unique<rift2d::GameObject>(this);
	auto enemyManager = gameObject->addComponent<EnemyManager>(3, 4.f);
	addGameObject(std::move(gameObject));

	if(const auto scoreComp = m_pPlayer->getComponent<ScoreComponent>())
	{
		enemyManager->onEnemySpawn()->subscribe([&](rift2d::GameObject* go)
			{
				if(const auto aiComp = go->getComponent<rift2d::AIController>())
				{
					aiComp->onDeathEvent()->subscribe([&]()
						{
							scoreComp->modify(gameSettings::NOBBIN_SCORE);
						});
				}
			});

		gameObject = std::make_unique<rift2d::GameObject>(this);
		gameObject->addComponent<ScoreDisplayComponent>(scoreComp);
		addGameObject(std::move(gameObject));
		
	}

	m_victoryObserverId= EmeraldManager::GetInstance().onFullyCollected()->subscribe([this]()
		{
			this->handleVictory();
		});
	

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
	EmeraldManager::GetInstance().onFullyCollected()->clearSubscribers();

}

void digger::GameScene::update()
{
	if(m_isLevelWon)
	{
		m_currentTime += rift2d::World::GetInstance().getDeltaTime();
		if (m_currentTime >= m_maxTime)
		{
			const auto nextLevel = std::make_unique<SkipLevelCommand>();
			nextLevel->execute();
		}
	}
}

void digger::GameScene::handleGameOver()
{
	rift2d::SceneManager::GetInstance().setActiveScene("MenuScene", true);
}

void digger::GameScene::handleVictory()
{
	m_isLevelWon = true;
	rift2d::InputManager::GetInstance().disableInput();
	rift2d::Physics::GetInstance().disable();
}
