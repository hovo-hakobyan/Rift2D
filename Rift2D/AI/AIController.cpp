#include "AIController.h"

#include <imgui.h>
#include <iostream>
#include <ostream>

#include "RigidBody2D.h"
#include "AStarPathfinding.h"
#include "GameObject.h"
#include "LevelGrid.h"
#include "Transform.h"
#include "World.h"

namespace rift2d
{
	AIController::AIController(GameObject* owner,  RigidBody2D* rb):
	BaseComponent(owner),m_pRB(rb)
	{
	}

	AIController::~AIController() = default;

	void AIController::init()
	{
		BaseComponent::init();

		const auto& levelGrid = LevelGrid::GetInstance();
		m_aStarPathfinding = std::make_unique<AStarPathfinding>(levelGrid.rows(), levelGrid.cols());

	}

	void AIController::moveTo(GameObject* pTarget)
	{
		if (!pTarget) return;

		const auto ownTransform = getOwner()->getTransform();
		if (!ownTransform) return;

		const auto targetTransform = pTarget->getTransform();
		if (!targetTransform) return;

		m_path = m_aStarPathfinding->findPath(ownTransform->getWorldPosition(), targetTransform->getWorldPosition());

		if (m_path.empty()) return;
		m_shouldMove = true;

	}

	void AIController::update()
	{
		if (!m_shouldMove) return;
		if (m_path.empty()) return;
		if (!m_pRB) return;

		const auto currentPos = getOwner()->getTransform()->getWorldPosition();
		const auto targetPos = m_path.front();
		const float distance = glm::length(targetPos - currentPos);
		constexpr float reachThreshold = 10.f;
		if(distance < reachThreshold)
		{
			m_path.pop_front();
			if(m_path.empty())
			{
				m_shouldMove = false;
				return;
			}
		}

		const auto targetdir = m_path.front() - getOwner()->getTransform()->getWorldPosition();
		const auto v = glm::normalize(targetdir) * m_speed * World::GetInstance().getDeltaTime();
		m_pRB->setLinearVelocity(v);
	}



	void AIController::onImGui()
	{
		if (!m_shouldDebugDraw) return;
		if (m_path.empty()) return;

		ImDrawList* drawList = ImGui::GetForegroundDrawList();

		for (size_t i = 0; i < m_path.size() - 1; ++i)
		{
			const glm::vec2& p1 = m_path[i];
			const glm::vec2& p2 = m_path[i + 1];

			drawList->AddLine(ImVec2(p1.x, p1.y), ImVec2(p2.x, p2.y), IM_COL32(255, 0, 0, 255), 2.0f);
		}

		for (const auto& point : m_path)
		{
			drawList->AddCircleFilled(ImVec2(point.x, point.y), 3.0f, IM_COL32(0, 255, 0, 255));
		}

	}


}
