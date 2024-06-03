#include "SkipLevelCommand.h"
#include "Scene.h"
#include "SceneManager.h"
#include "Digger/GameSettings.h"
#include "Scenes/GameScene.h"

void digger::SkipLevelCommand::execute()
{
	auto& sceneManager = rift2d::SceneManager::GetInstance();
	if(gameSettings::MAX_LEVELS - 1 <= m_currentLevelIdx)
	{
		sceneManager.setActiveScene("MenuScene", true);
		m_currentLevelIdx = 0;
		return;
	}

	const auto currentSceneName = "level" + std::to_string(m_currentLevelIdx);
	if (sceneManager.getActiveScene()->getName() == currentSceneName)
	{
		sceneManager.addScene(std::make_unique<GameScene>(++m_currentLevelIdx));
		sceneManager.setActiveScene("level" + std::to_string(m_currentLevelIdx),true);
	}

}
