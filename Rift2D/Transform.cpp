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

float rift2d::Transform::getLocalRotation(bool degrees) const
{
	if (degrees) return m_localRotDegrees;
	return glm::radians(m_localRotDegrees);
}


float rift2d::Transform::getWorldRotation(bool degrees)
{
	if (m_isDirty) updateWorldTransform();
	if (degrees) return m_worldRotDegrees;
	return glm::radians(m_worldRotDegrees);
}

void rift2d::Transform::setLocalRotation(float rot, bool degrees)
{
	if (degrees)
	{
		m_localRotDegrees = rot;
		return;
	}
	m_localRotDegrees = glm::degrees(rot);
	broadcastDirtyTransform();

}

void rift2d::Transform::addLocalRotation(float angle, bool degree)
{
	if(degree)
	{
		m_localRotDegrees += angle;
		return;
	}

	m_localRotDegrees += glm::degrees(angle);
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
	m_isDirty = false;
	const auto& parent = getOwner()->getParent();

	// No parent, world == local
	if(!parent)
	{
		m_worldPosition = m_localPosition;
		m_worldRotDegrees = m_localRotDegrees;
		return;
	}

	if (const auto parentTransform= parent->getTransform())
	{
		const auto parentPos = parentTransform->getWorldPosition();
		const float parentRot = parentTransform->getWorldRotation(false);

		
		const float cosAngle = glm::cos(parentRot);
		const float sinAngle = glm::sin(parentRot);
		const glm::vec3 rotatedLocalPos{
			m_localPosition.x * cosAngle - m_localPosition.y * sinAngle,
			m_localPosition.x * sinAngle - m_localPosition.y * cosAngle, m_localPosition.z };

		m_worldPosition = parentPos + rotatedLocalPos;
		m_worldRotDegrees = glm::degrees(parentRot) + m_localRotDegrees;
	}
	

}
