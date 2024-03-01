#include "Scene.h"
#include <algorithm>

using namespace rift2d;

unsigned int Scene::m_idCounter = 0;

Scene::Scene(const std::string& name) : m_name(name) {}

Scene::~Scene() = default;

GameObject* Scene::Add(std::unique_ptr<GameObject> object)
{
	if (!object)
	{
		return nullptr;
	}

	GameObject* rawPtr = object.get();
	m_objects.emplace_back(std::move(object));
	return rawPtr;
}

void Scene::Remove(GameObject* object)
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
		m_DeadObjects.push_back(it->get());
	}
	
}

void Scene::RemoveAll()
{
	End();
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

void rift2d::Scene::End()
{
	for (auto& object : m_objects)
	{
		object->End();
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
		objectToRemove->End();
		m_objects.erase(removeIt, m_objects.end());
	}
	m_DeadObjects.clear(); 
}


