#include "MoveCommand.h"
#include "GameObject.h"
#include "TimeManager.h"

rift2d::MoveCommand::MoveCommand(GameObject* obj, float speed):
m_pGameObj(obj),m_speed(speed)
{
}

void rift2d::MoveCommand::execute()
{
	const auto offset = getAxis() * m_speed * TimeManager::GetInstance().getDeltaTime();
	m_pGameObj->getTransform()->addLocalOffset(offset.x, offset.y);

}
