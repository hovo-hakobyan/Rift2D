#include "GoldFallingState.h"
#include "GameObject.h"
#include "GoldExplodingState.h"
#include "GoldIdleState.h"
#include "LevelGrid.h"
#include "RigidBody2D.h"
#include "Settings.h"
#include "StateComponent.h"
#include "Transform.h"
#include "Utils.h"

namespace digger
{
	void GoldFallingState::onEnter(rift2d::GameObject* gameObject)
	{
		if (const auto rigidBody = gameObject->getComponent<rift2d::RigidBody2D>())
		{
			rigidBody->setLinearVelocity({ 0.f,1.5f });
		}
		m_startPosition = gameObject->getTransform()->getWorldPosition();
		auto pos = m_startPosition;
		pos.x += settings::TILE_WIDTH / 2;
		pos.y += settings::TILE_HEIGHT / 2;

		m_startingTileIdx = rift2d::Utils::indexFromPosition(static_cast<int>(pos.x), static_cast<int>(pos.y), settings::NR_COLS);
	}

	void GoldFallingState::update(rift2d::GameObject* gameObject)
	{
		const auto stateComponent = gameObject->getComponent<rift2d::StateComponent>();
		if (!stateComponent) return;

		const auto currentPos = gameObject->getTransform()->getWorldPosition();
		m_fallDistance += glm::distance(currentPos, m_startPosition);
		m_startPosition = currentPos;

		if(hitsGround(gameObject))
		{
			if (m_fallDistance >= settings::TILE_HEIGHT * static_cast<float>(m_nrStoriesToExplode))
			{
				stateComponent->changeState(std::make_unique<GoldExplodingState>());
			}
			else
			{
				stateComponent->changeState(std::make_unique<GoldIdleState>());
			}
		}
	}

	void GoldFallingState::onExit(rift2d::GameObject* gameObject)
	{
		if (const auto rigidBody = gameObject->getComponent<rift2d::RigidBody2D>())
		{
			rigidBody->setLinearVelocity({ 0.f,0.f });
		}
	}

	bool GoldFallingState::hitsGround(rift2d::GameObject* go)
	{
		auto pos = go->getTransform()->getWorldPosition();
		pos.y += 5.f;
		const auto idx = rift2d::Utils::indexFromPosition(static_cast<int>(pos.x), static_cast<int>(pos.y), settings::NR_COLS);
		if (idx == m_startingTileIdx) return false;
		if (rift2d::LevelGrid::GetInstance().isTileEmpty(idx)) return false;
		return true;
	}
}

