#include "SceneManager.h"
#include "Scene.h"

rift2d::SceneManager::SceneManager() = default;
rift2d::SceneManager::~SceneManager() = default;

void rift2d::SceneManager::init()
{
	for (auto& scene : m_scenes)
	{
		scene->init();
	}
}

void rift2d::SceneManager::update()
{
	for(auto& scene : m_scenes)
	{
		scene->update();
	}
}

void rift2d::SceneManager::lateUpdate()
{
	for (auto& scene : m_scenes)
	{
		scene->lateUpdate();
	}
}

void rift2d::SceneManager::end()
{
}

rift2d::Scene& rift2d::SceneManager::createScene(const std::string& name)
{
	m_scenes.emplace_back(std::unique_ptr<Scene>(new Scene(name)));
	return *m_scenes.back();
}
