#include "MoveCommand.h"

#include "GameObject.h"
#include "RigidBody2D.h"
#include "TimeManager.h"
#include "Transform.h"

digger::MoveCommand::MoveCommand(rift2d::RigidBody2D* obj, float speed):
m_pRigidBody(obj),m_speed(speed)
{
}

void digger::MoveCommand::execute()
{	
	if (!m_pRigidBody) return;
	auto pos = m_pRigidBody->getOwner()->getTransform()->getWorldPosition();
	const auto impulse = getAxis() * m_speed * rift2d::TimeManager::GetInstance().getDeltaTime();
	m_pRigidBody->applyLinearImpulse(impulse, { pos.x,pos.y });

}
