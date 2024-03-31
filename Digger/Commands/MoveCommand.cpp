#include "MoveCommand.h"
#include "GameObject.h"
#include "TimeManager.h"
#include "Transform.h"

digger::MoveCommand::MoveCommand(rift2d::GameObject* obj, float speed):
m_pGameObj(obj),m_speed(speed)
{
}

void digger::MoveCommand::execute()
{
	const auto offset = getAxis() * m_speed * rift2d::TimeManager::GetInstance().getDeltaTime();
	m_pGameObj->getTransform()->addLocalOffset(offset.x, offset.y);

}
