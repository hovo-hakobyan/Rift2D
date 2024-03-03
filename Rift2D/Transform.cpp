#include "Transform.h"

#include <algorithm>

#include "GameObject.h"

rift2d::Transform::Transform(GameObject* owner):
BaseComponent(owner)
{
}

const glm::vec3& rift2d::Transform::getWorldPosition()
{
	if (m_isDirty) updateWorldPosition();
	return m_worldPosition;


}

void rift2d::Transform::setLocalPosition(const float x, const float y, const float z)
{
	m_localPosition.x = x;
	m_localPosition.y = y;
	m_localPosition.z = z;
	broadcastDirtyPos();
}

void rift2d::Transform::addLocalOffset(float x, float y)
{
	m_localPosition.x += x;
	m_localPosition.y += y;
	broadcastDirtyPos();
}


void rift2d::Transform::broadcastDirtyPos()
{
	m_isDirty = true;

	
	if(const auto owner = getOwner())
	{
		const auto& children = owner->getChildren();

		std::ranges::for_each(children, [](const std::shared_ptr<GameObject>& child)
		{
				if (const auto tr = child->getTransform())
				{
					tr->broadcastDirtyPos();
				}
		});
	}
}

void rift2d::Transform::updateWorldPosition()
{
	m_isDirty = false;
	const auto& parent = getOwner()->getParent();

	// No parent, world == local
	if(!parent)
	{
		m_worldPosition = m_localPosition;
		return;
	}

	if (const auto parentTransform= parent->getTransform())
	{
		const auto parentPos = parentTransform->getWorldPosition();
		m_worldPosition = parentPos + m_localPosition;
	}
	

}
