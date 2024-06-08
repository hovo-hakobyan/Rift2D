#include "Enemy.h"

#include <iostream>
#include <memory>
#include "AIController.h"
#include "BoxCollider2D.h"
#include "GameObject.h"
#include "RigidBody2D.h"
#include "Scene.h"
#include "SpriteComponent.h"
#include "Transform.h"
#include "Components/HealthComponent.h"

namespace digger
{
	void Enemy::setup(rift2d::GameObject* rootObj, rift2d::Scene* pScene)
	{
		if (!rootObj or !pScene) return;

		auto gameObject = std::make_unique<rift2d::GameObject>(pScene);
		rootObj->getTransform()->setLocalPosition(850.f, 100.f);

		const auto spriteComponent = gameObject->addComponent<rift2d::SpriteComponent>();
		spriteComponent->setTexture("nobbin.png");

		//Physics
		rift2d::RigidBodyDef rbDef;
		rbDef.type = rift2d::RiftBodyType::Dynamic;
		rbDef.fixedRotation = false;
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

		const auto pos = rootObj->getTransform()->getWorldPosition();
		rootObj->addComponent<rift2d::BoxCollider2D>(rift2d::BoxColliderInfo{ glm::vec2{pos.x,pos.y},
			glm::vec2{40.f,40.f},
			1.f,
			0.f,
			0.f,
			false,
			false,
			physics::CollisionGroup::Group4 });

		const auto aiController = gameObject->addComponent<rift2d::AIController>(rb);
		aiController->setDebugDraw(true);

		const auto enemy = pScene->addGameObject(std::move(gameObject));
		enemy->setParent(rootObj, false);

		
	}
}
