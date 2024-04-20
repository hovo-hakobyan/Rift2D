#include "MoneyPrefab.h"
#include "Scene.h"
#include "SpriteComponent.h"

void digger::MoneyPrefab::setup(rift2d::GameObject* rootObj, rift2d::Scene* pScene)
{
	if (!rootObj || !pScene) return;

	auto gameObject = pScene->createGameObject();
	const auto spriteComp = gameObject->addComponent<rift2d::SpriteComponent>();
	spriteComp->setTexture("money-bag.png");
	gameObject->setParent(rootObj, false);
}
