#include "ShootCommand.h"
#include "GameObject.h"
#include "Components/HealthComponent.h"

digger::ShootCommand::ShootCommand(rift2d::GameObject* shooter):
m_pShooter(shooter)
{
}


void digger::ShootCommand::execute()
{
	// now we just inflict damage,later we will check for collision and stuff
	if(m_pShooter)
	{
		if(const auto healthComponent = m_pShooter->getComponent<HealthComponent>())
		{
			healthComponent->modify(-1);
		}
	}
}

