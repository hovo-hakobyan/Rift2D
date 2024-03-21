#include "ShootCommand.h"
#include <iostream>

#include "GameObject.h"
#include "HealthComponent.h"

rift2d::ShootCommand::ShootCommand(GameObject* shooter):
m_pShooter(shooter)
{
}


void rift2d::ShootCommand::execute()
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

