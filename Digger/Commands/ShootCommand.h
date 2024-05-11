#pragma once
#include "Interfaces.h"


namespace rift2d
{
	class GameObject;
}

namespace digger
{

	class ShootCommand final : public rift2d::ICommand
	{
	public:
		explicit ShootCommand(rift2d::GameObject* shooter);
		void execute() override;
	private:
		rift2d::GameObject* m_pShooter{};
	};

}


