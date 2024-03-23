#include "EnemyPrefab.h"
#include "GameObject.h"
#include "HealthComponent.h"
#include "HealthDisplayComponent.h"
#include "InputManager.h"
#include "MoveCommand.h"
#include "SpriteComponent.h"
#include "Scene.h"
#include "ScoreCommand.h"
#include "ScoreComponent.h"
#include "ScoreDisplayComponent.h"
#include "ShootCommand.h"

void rift2d::EnemyPrefab::setup(GameObject* rootObj, Scene* pScene)
{
	if (!rootObj || !pScene) return;

	//create visuals
	auto gameObject = std::make_unique<rift2d::GameObject>(pScene);
	const auto spriteComponent = gameObject->addComponent<rift2d::SpriteComponent>();
	spriteComponent->setTexture("Tom.jpg");

	//bind input
	rift2d::InputManager::GetInstance().bindAxis2D(SDL_SCANCODE_D, SDL_SCANCODE_S, SDL_SCANCODE_A, SDL_SCANCODE_W,
		std::make_unique<rift2d::MoveCommand>(gameObject.get(), 150.f));

	//move
	gameObject->getTransform()->setLocalPosition(30.f, 180.f, 1.f);

	//add to scenegraph
	auto enemy = pScene->addGameObject(std::move(gameObject));
	enemy->setParent(rootObj, false);

	//add health component
	gameObject = std::make_unique<rift2d::GameObject>(pScene);
	auto windowSize = Renderer::GetInstance().getWindowSize();
	gameObject->getTransform()->setLocalPosition(windowSize.x - 100, 40, 1);
	auto healthComp = gameObject->addComponent<rift2d::HealthComponent>(3);
	gameObject->addComponent<rift2d::HealthDisplayComponent>(healthComp);

	//add to scenegraph
	enemy = pScene->addGameObject(std::move(gameObject));
	enemy->setParent(rootObj, true);

	//bind shooting to input
	rift2d::InputManager::GetInstance().bindAction(SDLK_c, InputEvent::Down, std::make_unique<ShootCommand>(rootObj));

	//add score
	auto scoreObj = std::make_unique<rift2d::GameObject>(pScene);
	scoreObj->getTransform()->setLocalPosition(10.f, 200.f, 1.f);
	auto scoreComp = scoreObj->addComponent<ScoreComponent>();
	scoreObj->addComponent<rift2d::ScoreDisplayComponent>(scoreComp);

	//add to scenegraph
	const auto score = pScene->addGameObject(std::move(scoreObj));
	score->setParent(rootObj, true);

	//add TEMP score collecting with input
	rift2d::InputManager::GetInstance().bindAction(SDLK_x, InputEvent::Down, std::make_unique<ScoreCommand>(rootObj));

}