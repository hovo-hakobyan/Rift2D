#include "GoldIdleState.h"
#include "GameObject.h"
#include "GoldFallingState.h"
#include "LevelGrid.h"
#include "RigidBody2D.h"
#include "Settings.h"
#include "StateComponent.h"
#include "Transform.h"
#include "Utils.h"

namespace digger
{
	void GoldIdleState::onEnter(rift2d::GameObject* gameObject)
	{
		if(const auto body = gameObject->getComponent<rift2d::RigidBody2D>())
		{
			body->setLinearVelocity({ 0.f,0.f });
		}

	}

	void GoldIdleState::update(rift2d::GameObject* gameObject)
	{
		if(shouldFall(gameObject))
		{
			if(const auto stateComponent = gameObject->getComponent<rift2d::StateComponent>())
			{
				stateComponent->changeState(std::make_unique<GoldFallingState>());
			}
		}
	}

	void GoldIdleState::onExit(rift2d::GameObject* /*gameObject*/)
	{
	}

	bool GoldIdleState::shouldFall(rift2d::GameObject* gameObj)
	{
		auto pos = gameObj->getTransform()->getWorldPosition();

		const auto idx = rift2d::Utils::indexFromPosition(static_cast<int>(pos.x), static_cast<int>(pos.y), settings::NR_COLS);
		const auto idxUnderneath = idx + settings::NR_COLS;
		if (rift2d::LevelGrid::GetInstance().isTileEmpty(idxUnderneath)) return true;
		return false;
	}
}
