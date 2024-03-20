#include "Scene.h"
#include <algorithm>
#include <ranges>

using namespace rift2d;

unsigned int Scene::m_idCounter = 0;

Scene::Scene(std::string name) : m_name(std::move(name)) {}

Scene::~Scene() = default;

GameObject* Scene::add(std::unique_ptr<GameObject> object)
{
	if (!object)
	{
		return nullptr;
	}

	auto obj = std::move(object);
	const auto rawPtr = obj.get();

	m_rootGameObjects.push_back(std::move(obj));
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
	//remove dead game objects
	processGameObjectRemovals();

	for (const auto& object : m_rootGameObjects)
	{
		object->processComponentRemovals();
	}

	
}

void Scene::processGameObjectRemovals()
{
	// Filter elements that are marked for destruction and call end
	//Invokes IsMarkedForDestruction for each child and if true, invokes end();
	for (const auto& child : m_rootGameObjects | std::views::filter(&GameObject::isMarkedForDestruction))
	{
		child->end();
	}

	m_rootGameObjects.erase(std::remove_if(m_rootGameObjects.begin(), m_rootGameObjects.end(),
		[](const std::unique_ptr<GameObject>& child) { return child->isMarkedForDestruction(); }),
		m_rootGameObjects.end());

	//filter elements that are not marked for destruction
	//Cannot bind function pointer because return is inverted
	for (const auto& child : m_rootGameObjects)
	{
		child->processGameObjectRemovals();
	}

}


