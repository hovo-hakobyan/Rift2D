#include "MenuScene.h"
#include "DiggerPrefab.h"
#include "EnemyPrefab.h"
#include "FPSComponent.h"
#include "ResourceManager.h"
#include "SpriteComponent.h"
#include "TextComponent.h"
#include "Transform.h"

rift2d::MenuScene::MenuScene():
Scene("MainMenuScene")
{
}

void rift2d::MenuScene::init()
{
	//Resources
	auto font = rift2d::ResourceManager::GetInstance().loadFont("Lingua.otf", 16);

	//Background
	auto gameObject = std::make_unique<rift2d::GameObject>(this);
	auto spriteComponent = gameObject->addComponent<rift2d::SpriteComponent>();
	spriteComponent->setTexture("background.tga");
	addGameObject(std::move(gameObject));

	//Logo
	gameObject = std::make_unique<rift2d::GameObject>(this);
	spriteComponent = gameObject->addComponent<rift2d::SpriteComponent>();
	spriteComponent->setTexture("logo.tga");
	gameObject->getTransform()->setLocalPosition(216.f, 180.f, 1.f);
	addGameObject(std::move(gameObject));

	//FPS 
	gameObject = std::make_unique<rift2d::GameObject>(this);
	gameObject->addComponent<rift2d::FPSComponent>();
	addGameObject(std::move(gameObject));

	addGameObjectFromPrefab<DiggerPrefab>();
	addGameObjectFromPrefab<EnemyPrefab>();

	// Main character text
	gameObject = std::make_unique<rift2d::GameObject>(this);
	gameObject->addComponent<rift2d::TextComponent>("Use the D-Pad to move Tom, X to inflict damage, A to collect pallets", font);
	gameObject->getTransform()->setLocalPosition(10.f, 50.f, 1.f);
	addGameObject(std::move(gameObject));

	// Enemy text
	gameObject = std::make_unique<rift2d::GameObject>(this);
	gameObject->addComponent<rift2d::TextComponent>("Use WASD to move the other Tom, C to inflict damage, X to collect pallets", font);
	gameObject->getTransform()->setLocalPosition(10.f, 70.f, 1.f);
	addGameObject(std::move(gameObject));
}
