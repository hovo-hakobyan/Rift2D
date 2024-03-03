#include "Transform.h"

#include <algorithm>

#include "GameObject.h"

rift2d::Transform::Transform(GameObject* owner):
BaseComponent(owner)
{
}

const glm::vec3& rift2d::Transform::getWorldPosition()
{
	if (m_isDirty) updateWorldTransform();
	return m_worldPosition;
}

void rift2d::Transform::setLocalPosition(const float x, const float y, const float z)
{
	m_localPosition.x = x;
	m_localPosition.y = y;
	m_localPosition.z = z;
	broadcastDirtyTransform();
}

void rift2d::Transform::addLocalOffset(float x, float y)
{
	m_localPosition.x += x;
	m_localPosition.y += y;
	broadcastDirtyTransform();
}



void rift2d::Transform::broadcastDirtyTransform()
{
	m_isDirty = true;

	
	if(const auto owner = getOwner())
	{
		const auto& children = owner->getChildren();

		std::ranges::for_each(children, [](const std::shared_ptr<GameObject>& child)
		{
				if (const auto tr = child->getTransform())
				{
					tr->broadcastDirtyTransform();
				}
		});
	}
}

void rift2d::Transform::updateWorldTransform()
{
	
	const auto& parent = getOwner()->getParent();

	// No parent, world == local
	if (!parent)
	{
		m_worldPosition = m_localPosition;
		return;
	}

	if (const auto parentTransform = parent->getTransform())
	{
		const auto parentPos = parentTransform->getWorldPosition();
		m_worldPosition = parentPos + m_localPosition;
		m_isDirty = false;
	}

}
