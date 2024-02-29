#include "SceneManager.h"
#include "Scene.h"

rift2d::SceneManager::SceneManager() = default;
rift2d::SceneManager::~SceneManager() = default;

void rift2d::SceneManager::Init()
{
	for (auto& scene : m_scenes)
	{
		scene->Init();
	}
}

void rift2d::SceneManager::Update()
{
	for(auto& scene : m_scenes)
	{
		scene->Update();
	}
}

void rift2d::SceneManager::LateUpdate()
{
	for (auto& scene : m_scenes)
	{
		scene->LateUpdate();
	}
}

rift2d::Scene& rift2d::SceneManager::CreateScene(const std::string& name)
{
	m_scenes.emplace_back(std::unique_ptr<Scene>(new Scene(name)));
	return *m_scenes.back();
}
