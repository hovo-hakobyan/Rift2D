#include "PhysicsTestScene.h"

#include "BoxCollider2D.h"
#include "DebugBoxComponent.h"
#include "RigidBody2D.h"
#include "SpriteComponent.h"

digger::PhysicsTestScene::PhysicsTestScene():
Scene("PhysicsTestScene")
{
}

void digger::PhysicsTestScene::init()
{
    //Logo
    auto go = createGameObject();
    go->getTransform()->setLocalPosition(50.f, 50.f,1.f);
    go->addComponent<rift2d::RigidBody2D>(rift2d::RigidBody2D::RiftBodyType::Dynamic);
    go->addComponent<rift2d::BoxCollider2D>(rift2d::BoxColliderInfo{ glm::vec2{go->getTransform()->getWorldPosition().x,go->getTransform()->getWorldPosition().y},
        glm::vec2{50.f,50.f},
    	1.f,
    	0.3f,
    	0.3f,
    	0.f,
		true});

    go = createGameObject();
    go->getTransform()->setLocalPosition(50.f, 250.f, 1.f);
    go->addComponent<rift2d::RigidBody2D>(rift2d::RigidBody2D::RiftBodyType::Static);
    go->addComponent<rift2d::BoxCollider2D>(rift2d::BoxColliderInfo{ glm::vec2{go->getTransform()->getWorldPosition().x,go->getTransform()->getWorldPosition().y},
        glm::vec2{350.f,20.f},
        1.f,
        0.3f,
        0.3f,
        0.f,
        true });


}
