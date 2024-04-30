#include "DiggerPrefab.h"

#include "BoxCollider2D.h"
#include "Commands/MoveCommand.h"
#include "Commands/ScoreCommand.h"
#include "Commands/ShootCommand.h"
#include "GameObject.h"
#include "InputManager.h"
#include "Renderer.h"
#include "RigidBody2D.h"
#include "SpriteComponent.h"
#include "Scene.h"
#include "Transform.h"
#include "Components/HealthComponent.h"
#include "Components/HealthDisplayComponent.h"


void digger::DiggerPrefab::setup(rift2d::GameObject* rootObj, rift2d::Scene* pScene)
{
	if (!rootObj || !pScene) return;

	auto gameObject = std::make_unique<rift2d::GameObject>(pScene);
	gameObject->getTransform()->setLocalPosition(150.f, 390.f, 1.f);
	//add sprite component for rendering 
	const auto spriteComponent = gameObject->addComponent<rift2d::SpriteComponent>();
	spriteComponent->setTexture("digger.png");

	//Physics
	rift2d::RigidBodyDef rbDef;
	rbDef.type = rift2d::RiftBodyType::Dynamic;
	rbDef.fixedRotation = false;
	rbDef.linearDamping = 5.f;
	auto rb = gameObject->addComponent<rift2d::RigidBody2D>(rbDef);
	const auto pos = rootObj->getTransform()->getWorldPosition();
	gameObject->addComponent<rift2d::BoxCollider2D>(rift2d::BoxColliderInfo{ glm::vec2{pos.x,pos.y},
		glm::vec2{64.f,64.f},
		1.f,
		1.f,
		0.1f,
		false });

	//add to scenegraph
	auto player = pScene->addGameObject(std::move(gameObject));
	player->setParent(rootObj, false);

	//Bind movement to input
	rift2d::InputManager::GetInstance().bindAxis2D(SDL_SCANCODE_D, SDL_SCANCODE_S, SDL_SCANCODE_A, SDL_SCANCODE_W,
		std::make_unique<MoveCommand>(rb, 30.f));

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
