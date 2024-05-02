#pragma once
#include <glm/vec2.hpp>
#include "BaseComponent.h"
#include <cstdint>

namespace rift2d
{
	class DebugBoxComponent;
}

namespace rift2d
{

	struct BoxColliderInfo
	{
		glm::vec2 center{};
		glm::vec2 size{};
		float density{};
		float friction{};
		float restitution{};
		bool debugVisualize{};
	};

	class BoxCollider2D final: public BaseComponent
	{
	public:
		BoxCollider2D(GameObject* owner,const BoxColliderInfo& info);
		virtual ~BoxCollider2D() override = default;
		BoxCollider2D(const BoxCollider2D& other) = delete;
		BoxCollider2D(BoxCollider2D&& other) = delete;
		BoxCollider2D& operator=(const BoxCollider2D& other) = delete;
		BoxCollider2D& operator=(BoxCollider2D&& other) = delete;

		virtual void init() override;

	private:
		BoxColliderInfo m_info;
		DebugBoxComponent* m_pDebugBox;
	};


}
