#include "PhysicsTestScene.h"

#include <format>
#include "BoxCollider2D.h"
#include "RigidBody2D.h"

digger::PhysicsTestScene::PhysicsTestScene():
Scene("PhysicsTestScene")
{
}

void digger::PhysicsTestScene::init()
{
    
    auto go = createGameObject();
    go->getTransform()->setLocalPosition(50.f, 0.f,1.f);

    rift2d::RigidBodyDef rbDef;
    rbDef.type = rift2d::RiftBodyType::Dynamic;
    rbDef.fixedRotation = false;
    go->addComponent<rift2d::RigidBody2D>(rbDef);
    go->addComponent<rift2d::BoxCollider2D>(rift2d::BoxColliderInfo{ glm::vec2{go->getTransform()->getWorldPosition().x,go->getTransform()->getWorldPosition().y},
        glm::vec2{50.f,50.f},
    	1.f,
    	0.3f,
    	1.f,
		true});

    go = createGameObject();
    go->getTransform()->setLocalPosition(0.f, 400.f, 1.f);
    rbDef.type = rift2d::RiftBodyType::Static;
    go->addComponent<rift2d::RigidBody2D>(rbDef);
    go->addComponent<rift2d::BoxCollider2D>(rift2d::BoxColliderInfo{ glm::vec2{go->getTransform()->getWorldPosition().x,go->getTransform()->getWorldPosition().y},
        glm::vec2{350.f,50.f},
        0.f,
        0.3f,
        0.5f,
        true });

}
