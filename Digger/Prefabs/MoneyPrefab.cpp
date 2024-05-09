#include "MoneyPrefab.h"

#include "BoxCollider2D.h"
#include "RigidBody2D.h"
#include "Scene.h"
#include "SpriteComponent.h"

void digger::MoneyPrefab::setup(rift2d::GameObject* rootObj, rift2d::Scene* pScene)
{
	if (!rootObj || !pScene) return;


	auto gameObject = pScene->createGameObject();
	const auto spriteComp = gameObject->addComponent<rift2d::SpriteComponent>();
	spriteComp->setTexture("money-bag.png");

	gameObject->addComponent<rift2d::RigidBody2D>(rift2d::RigidBodyDef{ rift2d::RiftBodyType::Kinematic,{},true,0.1f,"money" });
	const auto pos = rootObj->getTransform()->getWorldPosition();
	gameObject->addComponent<rift2d::BoxCollider2D>(rift2d::BoxColliderInfo
		{
			pos,
			glm::vec2{32.f,32.f},
			10.f,
			1.f,
			0.f,
			false,
			physics::CollisionGroup::Group3
		});

	gameObject->setParent(rootObj, false);
}
