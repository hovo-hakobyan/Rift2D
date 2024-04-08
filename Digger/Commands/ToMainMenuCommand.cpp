#include "ToMainMenuCommand.h"

#include "Scene.h"
#include "SceneManager.h"

void digger::ToMainMenuCommand::execute()
{
	auto& sceneManager = rift2d::SceneManager::GetInstance();
	if (sceneManager.getActiveScene()->getName() == "MenuScene") return;
	sceneManager.setActiveScene("MenuScene",true);
}
