#include "Enemy.h"

#include <memory>

#include "AIController.h"
#include "GameObject.h"
#include "Scene.h"
#include "SpriteComponent.h"
#include "Transform.h"
#include "World.h"

namespace digger
{
	void Enemy::setup(rift2d::GameObject* rootObj, rift2d::Scene* pScene)
	{
		if (!rootObj or !pScene) return;

		auto gameObject = std::make_unique<rift2d::GameObject>(pScene);
		rootObj->getTransform()->setLocalPosition(850.f, 100.f);

		const auto spriteComponent = gameObject->addComponent<rift2d::SpriteComponent>();
		spriteComponent->setTexture("nobbin.png");

		const auto aiController = gameObject->addComponent<rift2d::AIController>();
		aiController->setDebugDraw(true);

		const auto enemy = pScene->addGameObject(std::move(gameObject));
		enemy->setParent(rootObj, false);

		
	}
}
