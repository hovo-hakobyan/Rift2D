#pragma once
#include "Interfaces.h"

namespace rift2d
{
	class GameObject;
	class ShootCommand final : public rift2d::ICommand
	{
	public:
		explicit ShootCommand(GameObject* shooter);
		void execute() override;

	};

}


