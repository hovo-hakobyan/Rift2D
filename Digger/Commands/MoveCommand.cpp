#include "MoveCommand.h"
#include "RigidBody2D.h"
#include "World.h"
#include "Transform.h"

digger::MoveCommand::MoveCommand(rift2d::RigidBody2D* obj, float speed):
m_pRigidBody(obj),m_speed(speed)
{
}

void digger::MoveCommand::execute()
{	
	if (!m_pRigidBody) return;
	const auto axis= normalize(getAxis());

	const auto v = axis * m_speed * rift2d::World::GetInstance().getDeltaTime();
	m_pRigidBody->setLinearVelocity(v);
	m_pRigidBody->setRotation(axis);

}
