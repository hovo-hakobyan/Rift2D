#pragma once
#include "Singleton.h"
namespace rift2d
{
	class Rift2DEngine;
	class TimeManager final : public Singleton<TimeManager>
	{
		friend class Rift2DEngine;
	public:
		float getDeltaTime() const { return m_deltaTime; }
		float getFixedTime() const { return m_fixedTime; }
		
	private:
		float m_deltaTime = 0.0f;
		float m_fixedTime = 0.01666666667f;
	};
}