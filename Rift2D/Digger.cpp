#include "Digger.h"
#include "InputManager.h"
#include "MoveCommand.h"
#include "SpriteComponent.h"
#include "GameObject.h"

rift2d::Digger::Digger(rift2d::Scene* pScene):
RiftActor(pScene)
{
}
rift2d::Digger::~Digger() = default;
void rift2d::Digger::init()
{
	RiftActor::init();

	auto gameObject = std::make_unique<rift2d::GameObject>(this);
	auto spriteComponent = gameObject->addComponent<rift2d::SpriteComponent>();
	spriteComponent->setTexture("Tom.jpg");
	gameObject->getTransform()->setLocalPosition(30.f, 150.f, 1.f);
	rift2d::InputManager::GetInstance().bindAxis2D(rift2d::GamepadAxis2D::DPad, 0,
		std::make_unique<rift2d::MoveCommand>(gameObject.get(), 300.f));
	registerGameObject(std::move(gameObject));

}

void rift2d::Digger::update()
{
	RiftActor::update();

}

void rift2d::Digger::end()
{
	RiftActor::end();

}
