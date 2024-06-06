#include "DirtPrefab.h"
#include "BoxCollider2D.h"
#include "LevelGridTile.h"
#include "RigidBody2D.h"
#include "Scene.h"
#include "SpriteComponent.h"

void digger::DirtPrefab::setup(rift2d::GameObject* rootObj, rift2d::Scene* pScene)
{
	if (!rootObj || !pScene) return;

	const auto spriteComp = rootObj->addComponent<rift2d::SpriteComponent>();
	spriteComp->setTexture("dirt.png");
	rootObj->addComponent<rift2d::RigidBody2D>(rift2d::RigidBodyDef{ rift2d::RiftBodyType::Static,{},true,0.1f,"dirt" });

	const auto pos = rootObj->getTransform()->getWorldPosition();
	rootObj->addComponent<rift2d::BoxCollider2D>(rift2d::BoxColliderInfo{ glm::vec2{pos.x,pos.y},
	   glm::vec2{32.f,32.f},
	   1.f,
	   1.f,
	   0.f,
	   false,
	physics::CollisionGroup::Group2});
	rootObj->addComponent<rift2d::LevelGridTile>();

}
