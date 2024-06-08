#pragma once
#include <memory>

#include "Singleton.h"
#include "Subject.h"

namespace digger
{
	class EmeraldManager final : public rift2d::Singleton<EmeraldManager>
	{
	public:
		~EmeraldManager() override = default;

		void registerEmerald() { ++m_emeraldCounter; }
		void unregisterEmerald();

		rift2d::Subject<>* onFullyCollected() const { return m_pOnFullyCollected.get(); }

	private:
		friend Singleton;
		EmeraldManager();

		int m_emeraldCounter{ 0 };
		std::unique_ptr<rift2d::Subject<>> m_pOnFullyCollected;
	};
}
