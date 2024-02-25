#pragma once
#include "Singleton.h"
namespace rift2d
{
	class Rift2DEngine;
	class TimeManager final : public Singleton<TimeManager>
	{
		friend class Rift2DEngine;
	public:
		float GetDeltaTime() const { return m_DeltaTime; }
		float GetDesiredFPS() const { return m_DesiredFps; }
		
	private:
		float m_DeltaTime = 0.0f; 
		float m_FixedTime = 0.03f;
		float m_DesiredFps = 60.0f;
	};
}