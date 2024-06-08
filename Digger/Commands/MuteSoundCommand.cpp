#include "MuteSoundCommand.h"

#include "Locator.h"

void digger::MuteSoundCommand::execute()
{
	rift2d::ServiceLocator::getSoundSystem().mute();
}
