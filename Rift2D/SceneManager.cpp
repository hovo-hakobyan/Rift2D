#include "SceneManager.h"
#include "Scene.h"

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



rift2d::Scene& rift2d::SceneManager::CreateScene(const std::string& name)
{
	const auto& scene = std::shared_ptr<Scene>(new Scene(name));
	m_scenes.push_back(scene);
	return *scene;
}
