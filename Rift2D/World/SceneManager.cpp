#include "SceneManager.h"
#include "Exception.h"
#include "Scene.h"


rift2d::SceneManager::SceneManager() = default;
rift2d::SceneManager::~SceneManager() = default;

rift2d::Scene* rift2d::SceneManager::addScene(std::unique_ptr<Scene> scene)
{
	Scene* rawPtr{ scene.get() };
	auto name = scene->getName();
	const auto inserted = m_scenes.emplace(name, std::move(scene));
	if (!inserted.second)
	{
		THROW_RIFT_EXCEPTION("Scene with name" + name + "already exists", RiftExceptionType::Error);
	}
	return rawPtr;

}

void rift2d::SceneManager::setActiveScene(const std::string& sceneName, bool destroyCurrentScene)
{
	if (!m_scenes.contains(sceneName))
	{
		THROW_RIFT_EXCEPTION("Scene with name " + sceneName + " doesn't exist", RiftExceptionType::Error);
	}

	if (!m_pActiveScene)
	{
		m_pActiveScene = std::move(m_scenes[sceneName]);
	}
	else
	{
		m_pNextScene = std::move(m_scenes[sceneName]);
	}

	m_scenes.erase(sceneName);
	m_destroyCurrentScene = destroyCurrentScene;
}

bool rift2d::SceneManager::isValidScene(const std::string& sceneName) const
{
	return m_scenes.contains(sceneName);
}


void rift2d::SceneManager::init()
{
	if (!m_pActiveScene)
	{
		if (!m_scenes.empty())
		{
			m_pActiveScene = std::move(m_scenes.begin()->second);
			m_scenes.erase(m_pActiveScene->getName());
		}
		else
		{
			THROW_RIFT_EXCEPTION("No scenes found", RiftExceptionType::Error);
		}
	}

	m_pActiveScene->rootInit();
}

void rift2d::SceneManager::fixedUpdate()
{
	m_pActiveScene->rootFixedUpdate();
}

void rift2d::SceneManager::update() const
{
	m_pActiveScene->rootUpdate();
}

void rift2d::SceneManager::lateUpdate() const
{
	m_pActiveScene->rootLateUpdate();
}

void rift2d::SceneManager::end() const
{
	m_pActiveScene->rootEnd();
}

void rift2d::SceneManager::onImGui() const
{
	m_pActiveScene->rootOnImGui();
}

void rift2d::SceneManager::frameCleanup() 
{
	m_pActiveScene->rootFrameCleanup();

	if (m_pNextScene)
	{
		if(!m_destroyCurrentScene)
		{
			m_pActiveScene->disableScene();
			m_scenes[m_pActiveScene->getName()] = std::move(m_pActiveScene);
		}
		else
		{
			m_pActiveScene->rootEnd();
		}
		
		m_pActiveScene = std::move(m_pNextScene);
		m_destroyCurrentScene = true;

		if (!m_pActiveScene->isInitialized())
		{
			m_pActiveScene->rootInit();
		}
		m_pActiveScene->enableScene();
		m_pActiveScene->onActivate();
	}

}

rift2d::Scene* rift2d::SceneManager::getActiveScene() const
{
	return m_pActiveScene.get();
}

