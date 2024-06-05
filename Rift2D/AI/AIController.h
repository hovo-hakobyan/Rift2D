#pragma once
#include <vector>
#include <glm/vec2.hpp>

#include "BaseComponent.h"

namespace rift2d
{
	class AStarPathfinding;
}

namespace rift2d
{
	class AIController : public BaseComponent
	{
	public:
		AIController(GameObject* owner);
		virtual ~AIController() override;
		AIController(const AIController& other) = delete;
		AIController(AIController&& other) = delete;
		AIController& operator=(const AIController& other) = delete;
		AIController& operator=(AIController&& other) = delete;

		void moveTo(GameObject* pTarget);
		void update() override;
		void setDebugDraw(bool shouldDebugDraw) { m_shouldDebugDraw = shouldDebugDraw; }

		virtual void init() override;
		virtual void onImGui() override;
	private:
		std::unique_ptr<AStarPathfinding> m_aStarPathfinding;
		bool m_shouldMove{ false };
		bool m_shouldDebugDraw{ false };
		std::vector<glm::vec2> m_path;
	};


}
