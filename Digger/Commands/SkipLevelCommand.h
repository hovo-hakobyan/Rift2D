#pragma once
#include "Interfaces.h"

namespace digger
{
	class SkipLevelCommand : public rift2d::ICommand
	{
	public:
		SkipLevelCommand() = default;
		void execute() override;

	private:
		int m_currentLevelIdx{0};
	};


}
