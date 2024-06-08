#pragma once
#include "Commands/MoveCommand.h"

namespace digger
{
	class MuteSoundCommand final : public rift2d::ICommand
	{
	public:
		MuteSoundCommand() = default;
		void execute() override;
	};


}
