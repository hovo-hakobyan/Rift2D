#include "MenuScene.h"
#include "Exception.h"
#include "Prefabs/DiggerPrefab.h"
#include "Prefabs/EnemyPrefab.h"
#include "FPSComponent.h"
#include "ResourceManager.h"
#include "SpriteComponent.h"
#include "TextComponent.h"
#include "Transform.h"
#include "GameObject.h"
#include "WorldBuilder.h"
#include "Prefabs/DirtPrefab.h"
#include "Prefabs/EmeraldPrefab.h"
#include "Prefabs/MoneyPrefab.h"

digger::MenuScene::MenuScene():
Scene("MainMenuScene")
{
}

void digger::MenuScene::init()
{
	////Resources
	//auto font = rift2d::ResourceManager::GetInstance().loadFont("Lingua.otf", 16);


	////Logo
	//auto gameObject = std::make_unique<rift2d::GameObject>(this);
	//auto spriteComponent = gameObject->addComponent<rift2d::SpriteComponent>();
	//spriteComponent->setTexture("logo.tga");
	//gameObject->getTransform()->setLocalPosition(216.f, 180.f, 1.f);
	//addGameObject(std::move(gameObject));

	////FPS 
	//gameObject = std::make_unique<rift2d::GameObject>(this);
	//gameObject->addComponent<rift2d::FPSComponent>();
	//addGameObject(std::move(gameObject));

	//addGameObjectFromPrefab<DiggerPrefab>({100,0,1});
	//addGameObjectFromPrefab<EnemyPrefab>({50,0,1});

	//// Main character text
	//gameObject = std::make_unique<rift2d::GameObject>(this);
	//gameObject->addComponent<rift2d::TextComponent>("Use the D-Pad to move Tom, X to inflict damage, A to collect pallets", font);
	//gameObject->getTransform()->setLocalPosition(10.f, 50.f, 1.f);
	//addGameObject(std::move(gameObject));

	//// Enemy text
	//gameObject = std::make_unique<rift2d::GameObject>(this);
	//gameObject->addComponent<rift2d::TextComponent>("Use WASD to move the other Tom, C to inflict damage, X to collect pallets", font);
	//gameObject->getTransform()->setLocalPosition(10.f, 70.f, 1.f);
	//addGameObject(std::move(gameObject));

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
}
