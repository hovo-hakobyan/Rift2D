#include "Scene.h"
#include <algorithm>
#include <ranges>

#include "Exception.h"

using namespace rift2d;

unsigned int Scene::m_idCounter = 0;

Scene::Scene(std::string name) : m_name(std::move(name)) {}

void Scene::disableScene()
{
	
	for (const auto& element : m_rootGameObjects)
	{
		element->disable();
	}
}

void Scene::enableScene()
{
	for (const auto& element : m_rootGameObjects)
	{
		element->enable();
	}
}

Scene::~Scene() = default;

GameObject* Scene::addGameObject(std::unique_ptr<GameObject> object)
{
	if (!object)
	{
		return nullptr;
	}

	auto obj = std::move(object);
	const auto rawPtr = obj.get();

	m_rootObjectCache.push_back(std::move(obj));
	return rawPtr;
}

GameObject* Scene::createGameObject()
{
	auto go = std::make_unique<GameObject>(this);
	auto rawPtr = go.get();
	m_rootObjectCache.push_back(std::move(go));
	return rawPtr;
}

void Scene::remove(GameObject* object)
{
	if (!object)
	{
		return;
	}
	object->markForDestroy();

}

void Scene::removeAll()
{
	rootEnd();
	m_rootGameObjects.clear();
	m_rootObjectCache.clear();
}

std::unique_ptr<GameObject> Scene::releaseGameObject(GameObject* go)
{
	auto it = std::find_if(m_rootGameObjects.begin(), m_rootGameObjects.end(), [go](const auto& rootgo) {
		return rootgo.get() == go;
		});

	std::unique_ptr<GameObject> child;
	if (it != m_rootGameObjects.end())
	{
		child = std::move(*it);
		m_rootGameObjects.erase(it);
	}
	else
	{
		//look into cache
		auto cacheIt = std::find_if(m_rootObjectCache.begin(), m_rootObjectCache.end(), [go](const auto& cachego)
			{
				return cachego.get() == go;
			});

		if(cacheIt != m_rootObjectCache.end())
		{
			child = std::move(*cacheIt);
			m_rootObjectCache.erase(cacheIt);
		}
	}

	if (!child) THROW_RIFT_EXCEPTION("Game object is not owned by the scene, so it cannot be released", RiftExceptionType::Error);

	return child;
}

void Scene::rootInit()
{
	init();

	for (auto& object : m_rootGameObjects)
	{
		object->init();
	}
	m_isInitialized = true;
}

void Scene::rootFixedUpdate()
{
	fixedUpdate();

	for (const auto& object : m_rootGameObjects)
	{
		object->fixedUpdate();
	}
}

void Scene::rootUpdate() 
{
	update();

	for(const auto& object : m_rootGameObjects)
	{
		object->update();
	}

}

void Scene::rootLateUpdate() 
{
	lateUpdate();

	for (const auto& object : m_rootGameObjects)
	{
		object->lateUpdate();
	}
}

void rift2d::Scene::rootEnd()
{
	end();

	for (auto& object : m_rootGameObjects)
	{
		object->end();
	}
}

void Scene::rootOnImGui()
{
	onImGui();

	for (const auto& object : m_rootGameObjects)
	{
		object->onImGui();
	}
}

void Scene::rootFrameCleanup() 
{
	//add cached game objects
	processGameObjectCache();

	for (const auto& object : m_rootGameObjects)
	{
		object->frameCleanup();
	}

}



void Scene::processGameObjectCache()
{
	if (m_rootObjectCache.empty()) return;

	for (const auto& rootObjectCache : m_rootObjectCache)
	{
		rootObjectCache->init();
	}

	std::ranges::move(m_rootObjectCache, std::back_inserter(m_rootGameObjects));
	m_rootObjectCache.clear();
}


