#include "GameScene.h"
#include "Exception.h"
#include "WorldBuilder.h"
#include "Prefabs/DirtPrefab.h"
#include "Prefabs/EmeraldPrefab.h"
#include "Prefabs/MoneyPrefab.h"
#include "FPSComponent.h"
#include "Locator.h"
#include "Prefabs/DiggerPrefab.h"

digger::GameScene::GameScene():
Scene("GameScene")
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
		rift2d::WorldBuilder::buildLevel("level0");
	}
	catch (const rift2d::RiftException& e)
	{
		e.logToFile();
		throw;
	}

	auto gameObject = std::make_unique<rift2d::GameObject>(this);
	gameObject->addComponent<rift2d::FPSComponent>();
	addGameObject(std::move(gameObject));

	addGameObjectFromPrefab<DiggerPrefab>();

	//add sound mappings
	auto& ss = rift2d::ServiceLocator::getSoundSystem();
	ss.addSoundMapping(0, "laser.mp3");
	ss.addSoundMapping(1, "laser_explode.mp3");
	ss.addSoundMapping(2, "gold_tick.mp3");
}
