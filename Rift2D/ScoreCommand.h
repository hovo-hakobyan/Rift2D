#pragma once
#include "Interfaces.h"

namespace rift2d
{
	class GameObject;
	class ScoreCommand : public rift2d::ICommand
	{
		public:
			explicit ScoreCommand(GameObject* owner);
			void execute() override;
		private:
			GameObject* m_pOwner{};
	};


}
