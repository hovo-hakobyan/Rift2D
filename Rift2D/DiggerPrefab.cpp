#include "DiggerPrefab.h"
#include "GameObject.h"
#include "HealthComponent.h"
#include "HealthDisplayComponent.h"
#include "InputManager.h"
#include "MoveCommand.h"
#include "Scene.h"
#include "ScoreCommand.h"
#include "ScoreComponent.h"
#include "ScoreDisplayComponent.h"
#include "ShootCommand.h"
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

	//add to scenegraph
	auto player = pScene->addGameObject(std::move(gameObject));
	player->setParent(rootObj, true);

	//Bind movement to input
	rift2d::InputManager::GetInstance().bindAxis2D(rift2d::GamepadAxis2D::DPad, 0,
		std::make_unique<rift2d::MoveCommand>(player, 300.f));

	//add health component
	gameObject = std::make_unique<rift2d::GameObject>(pScene);
	auto windowSize = Renderer::GetInstance().getWindowSize();
	gameObject->getTransform()->setLocalPosition(windowSize.x - 100, 10, 1);
	auto healthComp = gameObject->addComponent<rift2d::HealthComponent>(3);
	gameObject->addComponent<rift2d::HealthDisplayComponent>(healthComp);

	//add to scenegraph
	player = pScene->addGameObject(std::move(gameObject));
	player->setParent(rootObj,true);

	//bind shooting to input
	rift2d::InputManager::GetInstance().bindAction(rift2d::GamepadKey::X, 0, InputEvent::Down,
		std::make_unique<rift2d::ShootCommand>(rootObj));

	//add score
	auto scoreObj = std::make_unique<rift2d::GameObject>(pScene);
	scoreObj->getTransform()->setLocalPosition(10.f, 180.f, 1.f);
	auto scoreComp = scoreObj->addComponent<ScoreComponent>();
	scoreObj->addComponent<rift2d::ScoreDisplayComponent>(scoreComp);

	//add to scenegraph
	const auto score = pScene->addGameObject(std::move(scoreObj));
	score->setParent(rootObj, true);

	//add TEMP score collecting with input
	rift2d::InputManager::GetInstance().bindAction(rift2d::GamepadKey::A, 0, InputEvent::Down,
		std::make_unique<rift2d::ScoreCommand>(rootObj));

}
