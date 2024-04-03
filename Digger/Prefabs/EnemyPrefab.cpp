#include "EnemyPrefab.h"
#include "GameObject.h"
#include "SpriteComponent.h"
#include "Scene.h"
#include "Transform.h"
#include "Commands/MoveCommand.h"
#include "Commands/ScoreCommand.h"
#include "Commands/ShootCommand.h"
#include "Components/HealthComponent.h"
#include "Components/HealthDisplayComponent.h"
#include "Components/ScoreComponent.h"
#include "Components/ScoreDisplayComponent.h"
#include "Renderer.h"
#include "InputManager.h"

void digger::EnemyPrefab::setup(rift2d::GameObject* rootObj, rift2d::Scene* pScene)
{
	if (!rootObj || !pScene) return;

	//create visuals
	auto gameObject = pScene->createGameObject();
	const auto spriteComponent = gameObject->addComponent<rift2d::SpriteComponent>();
	spriteComponent->setTexture("nobbin.png");

	//bind input
	rift2d::InputManager::GetInstance().bindAxis2D(SDL_SCANCODE_D, SDL_SCANCODE_S, SDL_SCANCODE_A, SDL_SCANCODE_W,
		std::make_unique<MoveCommand>(gameObject, 150.f));

	//move
	gameObject->getTransform()->setLocalPosition(30.f, 180.f, 1.f);

	gameObject->setParent(rootObj, false);

	//add health component
	gameObject = pScene->createGameObject();
	auto windowSize = rift2d::Renderer::GetInstance().getWindowSize();
	gameObject->getTransform()->setLocalPosition(windowSize.x - 100, 40, 1);
	auto healthComp = gameObject->addComponent<digger::HealthComponent>(3);
	gameObject->addComponent<digger::HealthDisplayComponent>(healthComp);

	//add to scenegraph
	gameObject->setParent(rootObj, true);

	//bind shooting to input
	rift2d::InputManager::GetInstance().bindAction(SDL_SCANCODE_C, rift2d::InputEvent::Down, std::make_unique<ShootCommand>(rootObj));

	//add score
	gameObject = pScene->createGameObject();
	gameObject->getTransform()->setLocalPosition(10.f, 200.f, 1.f);
	auto scoreComp = gameObject->addComponent<ScoreComponent>();
	gameObject->addComponent<ScoreDisplayComponent>(scoreComp);

	//add to scenegraph
	gameObject->setParent(rootObj, true);

	//add TEMP score collecting with input
	rift2d::InputManager::GetInstance().bindAction(SDL_SCANCODE_X, rift2d::InputEvent::Down, std::make_unique<ScoreCommand>(rootObj));

}
