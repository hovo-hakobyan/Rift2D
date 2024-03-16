#include "MoveCommand.h"
#include <format>
#include <iostream>

#include "GameObject.h"
#include "TimeManager.h"

rift2d::MoveCommand::MoveCommand(GameObject* obj, float speed):
Axis2DCommand(obj),m_speed(speed)
{
}

void rift2d::MoveCommand::execute()
{
	auto offset = m_axisValue * m_speed * TimeManager::GetInstance().getDeltaTime();
	getObject()->getTransform()->addLocalOffset(offset.x, offset.y);

}
