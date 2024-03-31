#pragma once
#include "Interfaces.h"

namespace rift2d
{
	class GameObject;
}

namespace digger
{
	class ScoreCommand : public rift2d::ICommand
	{
		public:
			explicit ScoreCommand(rift2d::GameObject* owner);
			void execute() override;
		private:
			rift2d::GameObject* m_pOwner{};
	};


}
