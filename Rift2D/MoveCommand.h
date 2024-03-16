#pragma once
#include "Axis2DCommand.h"

namespace rift2d
{
	class GameObject;
	class MoveCommand : public Axis2DCommand
	{
		public:
			explicit MoveCommand(GameObject* obj, float speed);
			void execute() override;

		private:
			float m_speed;
	};

}

