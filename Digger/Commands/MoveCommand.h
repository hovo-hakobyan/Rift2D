#pragma once
#include "Axis2DCommand.h"


namespace rift2d
{
	class GameObject;
}

namespace digger
{
	class MoveCommand : public rift2d::Axis2DCommand
	{
		public:
			explicit MoveCommand(rift2d::GameObject* obj, float speed);
			void execute() override;

		private:
			rift2d::GameObject* m_pGameObj{};
			float m_speed;
	};

}

