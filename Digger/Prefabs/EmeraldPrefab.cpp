#include "EmeraldPrefab.h"

#include "BoxCollider2D.h"
#include "RigidBody2D.h"
#include "Scene.h"
#include "SpriteComponent.h"
#include "Components/ScoreComponent.h"
#include "Digger/EmeraldManager.h"
#include "Digger/GameSettings.h"


void digger::EmeraldPrefab::setup(rift2d::GameObject* rootObj, rift2d::Scene* pScene)
{
	if (!rootObj || !pScene) return;

	//create visuals
	const auto spriteComponent = rootObj->addComponent<rift2d::SpriteComponent>();
	spriteComponent->setTexture("emerald.png");



	//Physics
	rift2d::RigidBodyDef rbDef;
	rbDef.type = rift2d::RiftBodyType::Static;
	rbDef.fixedRotation = false;
	rbDef.tag = "emerald";
	auto rb = rootObj->addComponent<rift2d::RigidBody2D>(rbDef);
	rb->onBeginOverlap([](rift2d::RigidBody2D*, rift2d::RigidBody2D* otherBody, rift2d::GameObject* go, rift2d::GameObject* otherGo)
		{
			if (otherBody->getTag() == "player")
			{
				if(auto comp = otherGo->getComponent<ScoreComponent>())
				{
					comp->modify(gameSettings::EMERALD_SCORE);
					go->markForDestroy();
					EmeraldManager::GetInstance().unregisterEmerald();
				}
			}

		});

	const auto pos = rootObj->getTransform()->getWorldPosition();
	rootObj->addComponent<rift2d::BoxCollider2D>(rift2d::BoxColliderInfo{ glm::vec2{pos.x,pos.y},
		glm::vec2{32.f,32.f},
		1.f,
		0.f,
		0.f,
		false,
		true,
		physics::CollisionGroup::Group6,
	physics::CollisionGroup::Group1});

	EmeraldManager::GetInstance().registerEmerald();
}
