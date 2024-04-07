#include "EmeraldPrefab.h"
#include "Scene.h"
#include "SpriteComponent.h"

void digger::EmeraldPrefab::setup(rift2d::GameObject* rootObj, rift2d::Scene* pScene)
{
	if (!rootObj || !pScene) return;

	//create visuals
	auto gameObject = pScene->createGameObject();
	const auto spriteComponent = gameObject->addComponent<rift2d::SpriteComponent>();
	spriteComponent->setTexture("emerald.png");
	gameObject->setParent(rootObj, false);
}
