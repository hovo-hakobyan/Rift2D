#include "MoneyPrefab.h"

#include <iostream>

#include "AIController.h"
#include "BoxCollider2D.h"
#include "Renderer.h"
#include "RigidBody2D.h"
#include "Scene.h"
#include "Settings.h"
#include "SpriteComponent.h"
#include "StateComponent.h"
#include "World.h"
#include "Commands/ToMainMenuCommand.h"
#include "Components/HealthComponent.h"
#include "Components/ScoreComponent.h"
#include "Digger/GameSettings.h"
#include "States/GoldFallingState.h"
#include "States/GoldIdleState.h"

void digger::MoneyPrefab::setup(rift2d::GameObject* rootObj, rift2d::Scene* pScene)
{
	if (!rootObj || !pScene) return;


	rift2d::GameObject* gameObject = pScene->createGameObject();
	auto spriteComp = gameObject->addComponent<rift2d::SpriteComponent>();
	spriteComp->setTexture("money-bag.png");

	auto rb =gameObject->addComponent<rift2d::RigidBody2D>(rift2d::RigidBodyDef{ rift2d::RiftBodyType::Kinematic,{},true,0.1f,"money" });
	auto pos = rootObj->getTransform()->getWorldPosition();
	pos.y += 32.f;
	gameObject->addComponent<rift2d::BoxCollider2D>(rift2d::BoxColliderInfo
		{
			pos,
			glm::vec2{10.f,20.f},
			50.f,
			0.f,
			0.f,
			false,
			true,
			physics::CollisionGroup::Group3,
			physics::CollisionGroup::Group1 | physics::CollisionGroup::Group4
		});


	rb->onBeginOverlap([](rift2d::RigidBody2D*, rift2d::RigidBody2D* otherBody, rift2d::GameObject* go, rift2d::GameObject* otherGameObject)
		{
			if (auto state = go->getComponent<rift2d::StateComponent>())
			{
				if (auto goldFallingState = dynamic_cast<GoldFallingState*>(state->getCurrentState()))
				{
					if (otherBody->getTag() == "player")
					{
						if (auto health = otherGameObject->getComponent<HealthComponent>())
						{
							health->modify(-1);
							
						}
						go->markForDestroy();
					}
					else if (otherBody->getTag() == "enemy")
					{
						if(auto ai = otherGameObject->getComponent<rift2d::AIController>())
						{
							ai->die();
						}
						else
						{
							if (auto comp =rift2d::World::GetInstance().getPlayer()->getComponent<ScoreComponent>())
							{
								comp->modify(gameSettings::NOBBIN_SCORE);
								otherGameObject->markForDestroy();
								auto command = std::make_unique<ToMainMenuCommand>();
								command->execute();
							}
						}
						go->markForDestroy();
					}
				}
			}
		});

	gameObject->addComponent<rift2d::StateComponent>()->changeState(std::make_unique<GoldIdleState>());

	gameObject->setParent(rootObj, false);


	
}
