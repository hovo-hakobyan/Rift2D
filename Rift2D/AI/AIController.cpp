#include "AIController.h"

#include <imgui.h>

#include "AStarPathfinding.h"
#include "GameObject.h"
#include "LevelGrid.h"
#include "Transform.h"

namespace rift2d
{
	AIController::AIController(GameObject* owner):
	BaseComponent(owner)
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
