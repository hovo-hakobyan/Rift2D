#include "Enemy.h"

#include <iostream>
#include <memory>
#include "AIController.h"
#include "BoxCollider2D.h"
#include "GameModeManager.h"
#include "GameObject.h"
#include "InputManager.h"
#include "RigidBody2D.h"
#include "Scene.h"
#include "SpriteComponent.h"
#include "Transform.h"
#include "Commands/MoveCommand.h"
#include "Components/HealthComponent.h"
#include "Digger/DiggerGameMode.h"

namespace digger
{
	void Enemy::setup(rift2d::GameObject* rootObj, rift2d::Scene* pScene)
	{
		if (!rootObj or !pScene) return;

		rootObj->getTransform()->setLocalPosition(850.f, 100.f);

		const auto spriteComponent = rootObj->addComponent<rift2d::SpriteComponent>();
		spriteComponent->setTexture("nobbin.png");

		//Physics
		rift2d::RigidBodyDef rbDef;
		rbDef.type = rift2d::RiftBodyType::Dynamic;
		rbDef.fixedRotation = true;
		rbDef.linearDamping = 10.f;
		rbDef.tag = "enemy";
		auto rb = rootObj->addComponent<rift2d::RigidBody2D>(rbDef);
		rb->onBeginOverlap([](rift2d::RigidBody2D*, rift2d::RigidBody2D* otherBody, rift2d::GameObject*, rift2d::GameObject* otherGameObject)
			{
				if (otherBody->getTag() == "player")
				{
					if(auto health = otherGameObject->getComponent<HealthComponent>())
					{
						health->modify(-1);
					}
				}

			});

		auto gameMode = dynamic_cast<DiggerGameMode*>(rift2d::GameModeManager::GetInstance().getGameMode());
		auto collisionGroups = physics::CollisionGroup::Group1 | physics::CollisionGroup::Group3;
		switch (gameMode->getPlayMode())
		{
		case PlayMode::Singleplayer:
			rootObj->addComponent<rift2d::AIController>(rb);
			break;
		case PlayMode::CoOp:
			break;
		case PlayMode::Versus:
			rift2d::InputManager::GetInstance().bindAxis2D(rift2d::GamepadAxis2D::DPad, 0,
				std::make_unique<MoveCommand>(rb, 350.f));
			collisionGroups = physics::CollisionGroup::Group1 | physics::CollisionGroup::Group2 |physics::CollisionGroup::Group3;
			break;
		}

		const auto pos = rootObj->getTransform()->getWorldPosition();
		rootObj->addComponent<rift2d::BoxCollider2D>(rift2d::BoxColliderInfo{ glm::vec2{pos.x,pos.y},
			glm::vec2{32.f,32.f},
			1.f,
			0.f,
			0.f,
			false,
			false,
			physics::CollisionGroup::Group4,
		collisionGroups});

	

	}
}
