#include "DiggerPrefab.h"
#include "Commands/MoveCommand.h"
#include "Commands/ScoreCommand.h"
#include "Commands/ShootCommand.h"
#include "GameObject.h"
#include "InputManager.h"
#include "Renderer.h"
#include "SpriteComponent.h"
#include "Scene.h"
#include "Transform.h"
#include "Components/HealthComponent.h"
#include "Components/HealthDisplayComponent.h"


void digger::DiggerPrefab::setup(rift2d::GameObject* rootObj, rift2d::Scene* pScene)
{
	if (!rootObj || !pScene) return;

	auto gameObject = std::make_unique<rift2d::GameObject>(pScene);

	//add sprite component for rendering 
	const auto spriteComponent = gameObject->addComponent<rift2d::SpriteComponent>();
	spriteComponent->setTexture("digger.png");

	//add to scenegraph
	auto player = pScene->addGameObject(std::move(gameObject));
	player->setParent(rootObj, false);

	//Bind movement to input
	rift2d::InputManager::GetInstance().bindAxis2D(rift2d::GamepadAxis2D::DPad, 0,
		std::make_unique<MoveCommand>(player, 300.f));

	//add health component
	gameObject = std::make_unique<rift2d::GameObject>(pScene);
	auto windowSize = rift2d::Renderer::GetInstance().getWindowSize();
	gameObject->getTransform()->setLocalPosition(windowSize.x - 100, 10, 1);
	auto healthComp = gameObject->addComponent<HealthComponent>(3);
	gameObject->addComponent<HealthDisplayComponent>(healthComp);

	//add to scenegraph
	player = pScene->addGameObject(std::move(gameObject));
	player->setParent(rootObj,true);

	//bind shooting to input
	rift2d::InputManager::GetInstance().bindAction(rift2d::GamepadKey::X, 0, rift2d::InputEvent::Down,
		std::make_unique<ShootCommand>(rootObj));


}
