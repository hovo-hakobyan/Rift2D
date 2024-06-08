#include "DiggerPrefab.h"
#include "BoxCollider2D.h"
#include "Commands/MoveCommand.h"
#include "Commands/ScoreCommand.h"
#include "GameObject.h"
#include "InputManager.h"
#include "Renderer.h"
#include "RigidBody2D.h"
#include "SpriteComponent.h"
#include "Scene.h"
#include "Settings.h"
#include "StateComponent.h"
#include "Transform.h"
#include "Components/HealthComponent.h"
#include "Components/HealthDisplayComponent.h"
#include "States/GoldCollectedState.h"
#include "States/GoldExplodingState.h"
#include "States/PlayerNormalState.h"


void digger::DiggerPrefab::setup(rift2d::GameObject* rootObj, rift2d::Scene* pScene)
{
	if (!rootObj || !pScene) return;

	//auto gameObject = std::make_unique<rift2d::GameObject>(pScene);
	rootObj->getTransform()->setLocalPosition(150.f, 390.f);


	//add sprite component for rendering 
	const auto spriteComponent = rootObj->addComponent<rift2d::SpriteComponent>();
	spriteComponent->setTexture("digger.png");

	//Physics
	rift2d::RigidBodyDef rbDef;
	rbDef.type = rift2d::RiftBodyType::Dynamic;
	rbDef.fixedRotation = false;
	rbDef.linearDamping = 10.f;
	rbDef.tag = "player";
	auto rb = rootObj->addComponent<rift2d::RigidBody2D>(rbDef);
	rb->onBeginOverlap([](rift2d::RigidBody2D*, rift2d::RigidBody2D* otherBody, rift2d::GameObject*, rift2d::GameObject* otherGameObject)
		{
			if(otherBody->getTag() == "dirt")
			{
				if(otherGameObject) otherGameObject->markForDestroy();
			}
			else if (otherBody->getTag() == "money")
			{
				if(const auto state = otherGameObject->getComponent<rift2d::StateComponent>())
				{
					if(dynamic_cast<GoldExplodingState*>(state->getCurrentState())) state->changeState(std::make_unique<GoldCollectedState>());
					
				}
			}
		
			
		});
	const auto pos = rootObj->getTransform()->getWorldPosition();
	rootObj->addComponent<rift2d::BoxCollider2D>(rift2d::BoxColliderInfo{ glm::vec2{pos.x,pos.y},
		glm::vec2{40.f,40.f},
		1.f,
		0.f,
		0.f,
		false,
		false,
		physics::CollisionGroup::Group1});


	//Bind movement to input
	rift2d::InputManager::GetInstance().bindAxis2D(rift2d::GamepadAxis2D::DPad, 0,
		std::make_unique<MoveCommand>(rb, 300.f), false, rootObj);

	rift2d::InputManager::GetInstance().bindAxis2D(SDL_SCANCODE_D, SDL_SCANCODE_S, SDL_SCANCODE_A, SDL_SCANCODE_W,
		std::make_unique<MoveCommand>(rb, 300.f));

	//add health component
	auto health = rootObj->addComponent<HealthComponent>(2);

	rootObj->addComponent<rift2d::StateComponent>()->changeState(std::make_unique<PlayerNormalState>(health));
}
