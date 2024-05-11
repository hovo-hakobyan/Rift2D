#include "MoneyPrefab.h"
#include "BoxCollider2D.h"
#include "Renderer.h"
#include "RigidBody2D.h"
#include "Scene.h"
#include "Settings.h"
#include "SpriteComponent.h"
#include "StateComponent.h"
#include "States/GoldIdleState.h"

void digger::MoneyPrefab::setup(rift2d::GameObject* rootObj, rift2d::Scene* pScene)
{
	if (!rootObj || !pScene) return;


	rift2d::GameObject* gameObject = pScene->createGameObject();
	const auto spriteComp = gameObject->addComponent<rift2d::SpriteComponent>();
	spriteComp->setTexture("money-bag.png");

	gameObject->addComponent<rift2d::RigidBody2D>(rift2d::RigidBodyDef{ rift2d::RiftBodyType::Kinematic,{},true,0.1f,"money" });
	const auto pos = rootObj->getTransform()->getWorldPosition();
	gameObject->addComponent<rift2d::BoxCollider2D>(rift2d::BoxColliderInfo
		{
			pos,
			glm::vec2{32.f,32.f},
			50.f,
			0.f,
			0.f,
			false,
			physics::CollisionGroup::Group3,
		});

	gameObject->addComponent<rift2d::StateComponent>()->changeState(std::make_unique<GoldIdleState>());

	gameObject->setParent(rootObj, false);

}
