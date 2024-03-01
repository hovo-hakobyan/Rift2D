#include "Scene.h"
#include <algorithm>

using namespace rift2d;

unsigned int Scene::m_idCounter = 0;

Scene::Scene(const std::string& name) : m_name(name) {}

Scene::~Scene() = default;

GameObject* Scene::add(std::unique_ptr<GameObject> object)
{
	if (!object)
	{
		return nullptr;
	}

	GameObject* rawPtr = object.get();
	m_objects.emplace_back(std::move(object));
	return rawPtr;
}

void Scene::remove(GameObject* object)
{
	if (!object)
	{
		return;
	}

	auto it = std::find_if(m_objects.begin(), m_objects.end(),
		[object](const std::unique_ptr<GameObject>& obj)
		{
			return obj.get() == object;
		});

	if (it != m_objects.end())
	{
		m_deadObjects.push_back(it->get());
	}
	
}

void Scene::removeAll()
{
	end();
	m_deadObjects.clear();
	m_objects.clear();
}

void Scene::init()
{
	for (auto& object : m_objects)
	{
		object->init();
	}
}

void Scene::update()
{
	for(auto& object : m_objects)
	{
		object->update();
	}

}

void Scene::lateUpdate()
{
	for (auto& object : m_objects)
	{
		object->lateUpdate();
	}

	//remove dead game objects
	processGameObjectRemovals();

	//for the remaining game objects, remove their dead components
	for (auto& object : m_objects)
	{
		object->processRemovals();
	}
}

void rift2d::Scene::end()
{
	for (auto& object : m_objects)
	{
		object->end();
	}
}

void Scene::processGameObjectRemovals()
{
	for ( auto* objectToRemove : m_deadObjects)
	{
		auto removeIt = std::remove_if(m_objects.begin(), m_objects.end(),
			[objectToRemove](const std::unique_ptr<GameObject>& obj) 
			{
				return obj.get() == objectToRemove;
			});
		objectToRemove->end();
		m_objects.erase(removeIt, m_objects.end());
	}
	m_deadObjects.clear(); 
}


