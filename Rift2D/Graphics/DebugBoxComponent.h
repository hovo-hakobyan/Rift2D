#pragma once
#include <glm/vec2.hpp>

#include "BaseComponent.h"
#include "Color.h"

namespace rift2d
{
	class DebugBoxComponent : public BaseComponent, public IRenderable
	{
	public:
		DebugBoxComponent(GameObject* owner,const RiftColor& color,const glm::vec2& size, bool isEnabled);
		virtual ~DebugBoxComponent() override = default;
		DebugBoxComponent(const DebugBoxComponent& other) = delete;
		DebugBoxComponent(DebugBoxComponent&& other) = delete;
		DebugBoxComponent& operator=(const DebugBoxComponent& other) = delete;
		DebugBoxComponent& operator=(DebugBoxComponent&& other) = delete;

		void render() const override;
		void setEnabled(bool flag) { m_isEnabled = flag; }

	private:
		RiftColor m_color;
		glm::vec2 m_size;
		bool m_isEnabled{false};
	};
}


