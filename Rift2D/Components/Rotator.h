#pragma once
#include "BaseComponent.h"

namespace  rift2d
{
	class Rotator final : public BaseComponent
	{
		float m_radius;
		float m_rotationSpeed;
		float m_currentAngleDegrees{0.0f};

	public:
		Rotator(GameObject* owner, float radius, float rotSpeedDegrees);
		virtual ~Rotator() override = default;
		Rotator(const Rotator& other) = delete;
		Rotator(Rotator&& other) = delete;
		Rotator& operator=(const Rotator& other) = delete;
		Rotator& operator=(Rotator&& other) = delete;

		virtual void update() override;
	};

}

