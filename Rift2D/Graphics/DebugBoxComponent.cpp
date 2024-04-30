#include "DebugBoxComponent.h"

#include "GameObject.h"
#include "Renderer.h"
#include "Transform.h"

rift2d::DebugBoxComponent::DebugBoxComponent(GameObject* owner, const RiftColor& color, const glm::vec2& size, bool isEnabled)
	: BaseComponent(owner), m_color(color),m_size(size),m_isEnabled(isEnabled)
{
}

void rift2d::DebugBoxComponent::render() const
{
	if (!m_isEnabled) return;
	if(const auto owner = getOwner())
	{
		auto pos = owner->getTransform()->getWorldPosition();
		Renderer::GetInstance().renderBox( pos.x, pos.y, m_size.x, m_size.y, m_color);
		
	}
}
