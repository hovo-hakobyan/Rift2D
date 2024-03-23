#include "ScoreCommand.h"
#include "ScoreComponent.h"
#include "GameObject.h"

rift2d::ScoreCommand::ScoreCommand(GameObject* owner):
m_pOwner(owner)
{
}

void rift2d::ScoreCommand::execute()
{
	if(m_pOwner)
	{
		if(auto score = m_pOwner->getComponent<ScoreComponent>())
		{
			score->modify(100);
		}
	}
}
