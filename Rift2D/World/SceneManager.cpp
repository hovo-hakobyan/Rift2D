#include "SceneManager.h"
#include "Scene.h"


rift2d::SceneManager::SceneManager() = default;
rift2d::SceneManager::~SceneManager() = default;

rift2d::Scene* rift2d::SceneManager::addScene(std::unique_ptr<Scene> scene)
{
	const auto rawPtr = scene.get();
	m_scenes.push_back(std::move(scene));
	++m_activeSceneIdx;

	return rawPtr;

}

void rift2d::SceneManager::setActiveScene(int sceneIdx)
{
	if (static_cast<int>( m_scenes.size()) <= sceneIdx) return;
	m_newSceneIdx = sceneIdx;
	m_shouldSwapScene = true;
}


void rift2d::SceneManager::init() const
{
	m_scenes[m_activeSceneIdx]->rootInit();
}

void rift2d::SceneManager::update() const
{
	m_scenes[m_activeSceneIdx]->rootUpdate();
}

void rift2d::SceneManager::lateUpdate() const
{
	m_scenes[m_activeSceneIdx]->rootLateUpdate();
}

void rift2d::SceneManager::end() const
{
	m_scenes[m_activeSceneIdx]->rootEnd();
}

void rift2d::SceneManager::onImGui() const
{
	m_scenes[m_activeSceneIdx]->rootOnImGui();
}

void rift2d::SceneManager::frameCleanup() 
{
	m_scenes[m_activeSceneIdx]->rootFrameCleanup();

	if (m_shouldSwapScene)
	{
		m_activeSceneIdx = m_newSceneIdx;
		m_shouldSwapScene = false;
		if (!m_scenes[m_activeSceneIdx]->isInitialized()) m_scenes[m_activeSceneIdx]->rootInit();
	}
}
