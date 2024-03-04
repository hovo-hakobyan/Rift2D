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
	end();
	m_rootGameObjects.clear();
}

void Scene::init() const
{
	for (auto& object : m_rootGameObjects)
	{
		object->init();
	}
	
}

void Scene::update() const
{
	for(auto& object : m_rootGameObjects)
	{
		object->update();
	}

}

void Scene::lateUpdate() const
{
	for (const auto& object : m_rootGameObjects)
	{
		object->lateUpdate();
	}
}

void rift2d::Scene::end() const
{
	for (auto& object : m_rootGameObjects)
	{
		object->end();
	}
}

void Scene::frameCleanup() 
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


