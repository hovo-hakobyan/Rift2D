#pragma once
#include "Axis2DCommand.h"


namespace rift2d
{
	class RigidBody2D;
}

namespace rift2d
{
	class GameObject;
}

namespace digger
{
	class MoveCommand : public rift2d::Axis2DCommand
	{
		public:
			explicit MoveCommand(rift2d::RigidBody2D* obj, float speed);
			void execute() override;

		private:
			rift2d::RigidBody2D* m_pRigidBody{};
			float m_speed;
	};

}

