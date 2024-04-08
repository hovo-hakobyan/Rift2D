#pragma once
#include "MoveCommand.h"

namespace digger
{
	class ToMainMenuCommand : public rift2d::ICommand
	{
	public:
		void execute() override;
	};


}
