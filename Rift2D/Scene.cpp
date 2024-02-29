#include "Scene.h"
#include <algorithm>

using namespace rift2d;

unsigned int Scene::m_idCounter = 0;

Scene::Scene(const std::string& name) : m_name(name) {}

Scene::~Scene() = default;

void Scene::Add(std::unique_ptr<GameObject> object)
{
	m_objects.emplace_back(std::move(object));
}

void Scene::Remove(GameObject* object)
{
	auto it = std::find_if(m_objects.begin(), m_objects.end(),
		[object](const std::unique_ptr<GameObject>& obj)
		{
			return obj.get() == object;
		});

	if (it != m_objects.end())
	{
		m_DeadObjects.push_back(it->get());
	}
	
}

void Scene::RemoveAll()
{
	m_DeadObjects.clear();
	m_objects.clear();
}

void Scene::Init()
{
	for (auto& object : m_objects)
	{
		object->Init();
	}
}

void Scene::Update()
{
	for(auto& object : m_objects)
	{
		object->Update();
	}

}

void Scene::LateUpdate()
{
	for (auto& object : m_objects)
	{
		object->LateUpdate();
	}

	//Remove dead game objects
	ProcessGameObjectRemovals();

	//for the remaining game objects, remove their dead components
	for (auto& object : m_objects)
	{
		object->ProcessRemovals();
	}
}

void Scene::ProcessGameObjectRemovals()
{
	for ( auto* objectToRemove : m_DeadObjects)
	{
		auto removeIt = std::remove_if(m_objects.begin(), m_objects.end(),
			[objectToRemove](const std::unique_ptr<GameObject>& obj) 
			{
				return obj.get() == objectToRemove;
			});
		m_objects.erase(removeIt, m_objects.end());
	}
	m_DeadObjects.clear(); 
}


