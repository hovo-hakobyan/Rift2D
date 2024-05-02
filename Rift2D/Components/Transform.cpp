#include "Transform.h"

#include <algorithm>

#include "GameObject.h"

rift2d::Transform::Transform(GameObject* owner):
BaseComponent(owner)
{
}

const glm::vec2& rift2d::Transform::getWorldPosition()
{
	if (m_isDirty) updateWorldTransform();
	return m_worldPosition;
}

void rift2d::Transform::setLocalPosition(const float x, const float y)
{
	m_localPosition.x = x;
	m_localPosition.y = y;
	broadcastDirtyTransform();
}

void rift2d::Transform::setLocalPosition(const glm::vec2& pos)
{
	m_localPosition = pos;
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

		std::ranges::for_each(children, [](const std::unique_ptr<GameObject>& child)
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
		m_worldRotation = m_localRotation;
	}
	else if (const auto parentTransform = parent->getTransform())
	{
		const auto parentPos = parentTransform->getWorldPosition();
		const float parentRot = parentTransform->getWorldRotation();

		const float cosAngle = glm::cos(parentRot);
		const float sinAngle = glm::sin(parentRot);

		m_worldPosition = glm::vec2{
			parentPos.x + m_localPosition.x * cosAngle - m_localPosition.y * sinAngle,
			parentPos.y + m_localPosition.x * sinAngle + m_localPosition.y * cosAngle };

		m_worldRotation = parentRot + m_localRotation;
	}
	m_isDirty = false;
}
void rift2d::Transform::setWorldPosition(float x, float y)
{
	const auto& parent = getOwner()->getParent();

	if(!parent)
	{
		m_localPosition = glm::vec2{x,y};
	}
	else
	{
		const auto transform = getOwner()->getParent()->getTransform();
		const auto parentPos = transform->getWorldPosition();
		const auto parentRot = transform->getWorldRotation();

		const float cosAngle = glm::cos(parentRot);
		const float sinAngle = glm::sin(parentRot);

		m_localPosition = glm::vec2
		{
			(x - parentPos.x) * cosAngle - (y - parentPos.y) * sinAngle,
			(x - parentPos.x) * sinAngle + (y - parentPos.y) * cosAngle
		};
	}

	broadcastDirtyTransform();
}

void rift2d::Transform::setWorldPosition(const glm::vec2& pos)
{
	setWorldPosition(pos.x, pos.y);
}

float rift2d::Transform::getLocalRotation(bool inDegrees) const
{
	if (inDegrees) return glm::degrees(m_localRotation);
	return m_localRotation;
}

float rift2d::Transform::getWorldRotation(bool inDegrees)
{
	if (m_isDirty) updateWorldTransform();
	if (inDegrees) return glm::degrees(m_worldRotation);
	return m_worldRotation;
}

void rift2d::Transform::setLocalRotation(float angle, bool isDegree)
{
	if (isDegree) m_localRotation = glm::radians(angle);
	else m_localRotation = angle;
	broadcastDirtyTransform();
}

void rift2d::Transform::setWorldRotation(float angle, bool isDegree)
{
	const auto worldRot = getWorldRotation();
	if (isDegree) m_localRotation += glm::radians(angle) - worldRot;
	else m_localRotation += angle - worldRot;
	broadcastDirtyTransform();
}

void rift2d::Transform::rotate(float angle, bool isDegree)
{
	if (isDegree) m_localRotation += glm::radians(angle);
	else m_localRotation += angle;
	broadcastDirtyTransform();
}
