#include "Rotator.h"

#include <iostream>
#include <glm/trigonometric.hpp>

#include "GameObject.h"
#include "TimeManager.h"

rift2d::Rotator::Rotator(GameObject* owner, float radius, float rotSpeedDegrees):
BaseComponent(owner),m_radius(radius),m_rotationSpeed(rotSpeedDegrees)
{
}

void rift2d::Rotator::update()
{
	const float deltaTime = TimeManager::GetInstance().getDeltaTime();
	m_currentAngleDegrees += m_rotationSpeed * deltaTime;

	if (m_currentAngleDegrees >= 360.f) m_currentAngleDegrees -= 360.f;
	if(m_currentAngleDegrees <= -360.f) m_currentAngleDegrees += 360.f;

	const float currentAngleRadians = glm::radians(m_currentAngleDegrees);

	if(auto owner = getOwner())
	{
		if (auto transform = owner->getTransform())
		{
			glm::vec2 offset{ m_radius * glm::cos(currentAngleRadians) ,m_radius * glm::sin(currentAngleRadians) };
			transform->setLocalPosition(offset.x, offset.y,1.0f);

			
		}
	}
	
	
}
