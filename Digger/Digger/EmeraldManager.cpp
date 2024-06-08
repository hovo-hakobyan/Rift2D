#include "EmeraldManager.h"

namespace digger
{
	EmeraldManager::EmeraldManager():
	m_pOnFullyCollected(std::make_unique<rift2d::Subject<>>())
	{
	}

	void EmeraldManager::unregisterEmerald()
	{
		--m_emeraldCounter;
		if(m_emeraldCounter <= 0)
		{
			m_emeraldCounter = 0;
			m_pOnFullyCollected->notify();
		}

	}

	
}
