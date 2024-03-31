#include "ScoreCommand.h"
#include "GameObject.h"
#include "Components/ScoreComponent.h"

digger::ScoreCommand::ScoreCommand(rift2d::GameObject* owner):
m_pOwner(owner)
{
}

void digger::ScoreCommand::execute()
{
	if(m_pOwner)
	{
		if(auto score = m_pOwner->getComponent<ScoreComponent>())
		{
			score->modify(100);
		}
	}
}
