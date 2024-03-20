#include "DiggerPrefab.h"
#include "GameObject.h"
#include "InputManager.h"
#include "MoveCommand.h"
#include "Scene.h"
#include "SpriteComponent.h"


void rift2d::DiggerPrefab::setup(GameObject* rootObj, Scene* pScene)
{
	if (!rootObj || !pScene) return;

	auto gameObject = std::make_unique<rift2d::GameObject>(pScene);
	const auto spriteComponent = gameObject->addComponent<rift2d::SpriteComponent>();
	spriteComponent->setTexture("Tom.jpg");
	gameObject->getTransform()->setLocalPosition(30.f, 150.f, 1.f);
	rift2d::InputManager::GetInstance().bindAxis2D(rift2d::GamepadAxis2D::DPad, 0,
		std::make_unique<rift2d::MoveCommand>(gameObject.get(), 300.f));
	auto player = pScene->addGameObject(std::move(gameObject));
	player->setParent(rootObj,false);
}
