#include "Scene.h"
#include "GameObject.h"

#include <algorithm>

using namespace rift2d;

unsigned int Scene::m_idCounter = 0;

Scene::Scene(const std::string& name) : m_name(name) {}



Scene::~Scene() = default;

void Scene::Add(std::shared_ptr<GameObject> object)
{
	m_objects.emplace_back(std::move(object));
}

void Scene::Remove(std::shared_ptr<GameObject> object)
{
	auto it = std::find(m_objects.begin(), m_objects.end(), object);
	if (it != m_objects.end())
	{
		m_DeadObjects.push_back(object);
	}
}

void Scene::RemoveAll()
{
	m_objects.clear();
}

void rift2d::Scene::Init()
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

	ProcessGameObjectRemovals();

	for (auto& object : m_objects)
	{
		object->ProcessRemovals();
	}

	
}

void rift2d::Scene::ProcessGameObjectRemovals()
{
	for (const auto& objectToRemove : m_DeadObjects)
	{
		m_objects.erase(std::remove(m_objects.begin(), m_objects.end(), objectToRemove), m_objects.end());
	}
	m_DeadObjects.clear(); 
}


