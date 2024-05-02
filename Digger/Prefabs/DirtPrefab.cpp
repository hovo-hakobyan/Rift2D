#include "DirtPrefab.h"
#include "BoxCollider2D.h"
#include "RigidBody2D.h"
#include "Scene.h"
#include "SpriteComponent.h"

void digger::DirtPrefab::setup(rift2d::GameObject* rootObj, rift2d::Scene* pScene)
{
	if (!rootObj || !pScene) return;

	const auto gameObject = pScene->createGameObject();
	const auto spriteComp = gameObject->addComponent<rift2d::SpriteComponent>();
	spriteComp->setTexture("dirt.png");
	gameObject->addComponent<rift2d::RigidBody2D>(rift2d::RigidBodyDef{ rift2d::RiftBodyType::Static,{},true });

	const auto pos = rootObj->getTransform()->getWorldPosition();
	gameObject->addComponent<rift2d::BoxCollider2D>(rift2d::BoxColliderInfo{ glm::vec2{pos.x,pos.y},
	   glm::vec2{32.f,32.f},
	   1.f,
	   1.f,
	   0.f,
	   false});

	gameObject->setParent(rootObj,false);
}
