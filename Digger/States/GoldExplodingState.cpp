#include "GoldExplodingState.h"

#include "GameObject.h"
#include "Locator.h"
#include "SpriteComponent.h"

namespace digger
{
	void GoldExplodingState::onEnter(rift2d::GameObject* gameObject)
	{
		if(const auto sprite = gameObject->getComponent<rift2d::SpriteComponent>())
		{
			sprite->setTexture("money.png",{0.f,-8.f});
		}

		rift2d::ServiceLocator::getSoundSystem().play(1);
	}

	void GoldExplodingState::update(rift2d::GameObject* /*gameObject*/)
	{
	}

	void GoldExplodingState::onExit(rift2d::GameObject* /*gameObject*/)
	{
	}
}
