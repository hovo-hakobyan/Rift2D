#include "ShootCommand.h"
#include <iostream>

rift2d::ShootCommand::ShootCommand(GameObject* shooter):
ICommand(shooter)
{
}


void rift2d::ShootCommand::execute()
{
	std::cout << "Fired a bullet\n";
}

