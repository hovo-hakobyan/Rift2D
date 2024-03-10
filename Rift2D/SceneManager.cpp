#include "SceneManager.h"
#include "Scene.h"

rift2d::SceneManager::SceneManager() = default;
rift2d::SceneManager::~SceneManager() = default;

void rift2d::SceneManager::init() const
{
	m_scenes[m_currentSceneIdx]->init();
}

void rift2d::SceneManager::update() const
{
	m_scenes[m_currentSceneIdx]->update();
}

void rift2d::SceneManager::lateUpdate() const
{
	m_scenes[m_currentSceneIdx]->lateUpdate();
}

void rift2d::SceneManager::end() const
{
	m_scenes[m_currentSceneIdx]->end();
}

void rift2d::SceneManager::onImGui() const
{
	m_scenes[m_currentSceneIdx]->onImGui();
}

void rift2d::SceneManager::frameCleanup() const
{
	m_scenes[m_currentSceneIdx]->frameCleanup();
}

rift2d::Scene& rift2d::SceneManager::createScene(const std::string& name)
{
	m_scenes.emplace_back(std::unique_ptr<Scene>(new Scene(name)));
	++m_currentSceneIdx;
	return *m_scenes.back();
}
