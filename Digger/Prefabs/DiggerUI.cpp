#include "DiggerUI.h"
#include "GameObject.h"
#include "RiftUI.h"
#include "Scene.h"
#include "Settings.h"
#include "Components/HealthDisplayComponent.h"

void digger::DiggerUI::setup(rift2d::GameObject* rootObj, rift2d::Scene* pScene)
{
	if (!rootObj || !pScene) return;

	auto& riftUI = rift2d::RiftUI::GetInstance();
	riftUI.init(rootObj);

	auto healthDisplay = std::make_unique<rift2d::GameObject>(pScene);
	healthDisplay->getTransform()->setWorldPosition(riftSettings::WINDOW_WIDTH - 100, 10);
	healthDisplay->addComponent<HealthDisplayComponent>(nullptr);

	const auto healthDisplayPtr = pScene->addGameObject(std::move(healthDisplay));
	healthDisplayPtr->setParent(rootObj, true);
}
