#include "DiggerPrefab.h"
#include "GameObject.h"
#include "HealthComponent.h"
#include "InputManager.h"
#include "MoveCommand.h"
#include "Scene.h"
#include "SpriteComponent.h"


void rift2d::DiggerPrefab::setup(GameObject* rootObj, Scene* pScene)
{
	if (!rootObj || !pScene) return;

	auto gameObject = std::make_unique<rift2d::GameObject>(pScene);

	//add sprite component for rendering 
	const auto spriteComponent = gameObject->addComponent<rift2d::SpriteComponent>();
	spriteComponent->setTexture("Tom.jpg");

	//move
	gameObject->getTransform()->setLocalPosition(30.f, 150.f, 1.f);

	//Bind to input
	rift2d::InputManager::GetInstance().bindAxis2D(rift2d::GamepadAxis2D::DPad, 0,
		std::make_unique<rift2d::MoveCommand>(gameObject.get(), 300.f));

	//add to scenegraph
	auto player = pScene->addGameObject(std::move(gameObject));
	player->setParent(rootObj, true);

	//add health component
	gameObject = std::make_unique<rift2d::GameObject>(pScene);
	auto windowSize = Renderer::GetInstance().getWindowSize();
	gameObject->getTransform()->setLocalPosition(windowSize.x - 100, 10, 1);
	gameObject->addComponent<rift2d::HealthComponent>(3,true);

	//add to scenegraph
	player = pScene->addGameObject(std::move(gameObject));
	player->setParent(rootObj, true);
}
