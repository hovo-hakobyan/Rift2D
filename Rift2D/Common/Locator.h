#pragma once
#include <memory>
#include "Interfaces.h"

namespace rift2d
{
	class ServiceLocator final
	{
	public:
		static ISoundSystem& getSoundSystem() { return *m_ssInstance; }
		static void registerSoundSystem(std::unique_ptr<ISoundSystem>&& ss) { m_ssInstance = std::move(ss); }
	private:
		inline static std::unique_ptr<ISoundSystem> m_ssInstance;
	};

}
