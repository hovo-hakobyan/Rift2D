#include "Scene.h"
#include <algorithm>

using namespace rift2d;

unsigned int Scene::m_idCounter = 0;

Scene::Scene(const std::string& name) : m_name(name) {}

Scene::~Scene() = default;

std::weak_ptr<GameObject> Scene::add(std::shared_ptr<GameObject> object)
{
	if (!object)
	{
		return {};
	}

	auto obj = std::move(object);
	obj->setOwningScene(this);

	m_rootGameObjects.push_back(obj);
	return obj;
}

void Scene::remove(const std::shared_ptr<GameObject>& gameObject)
{
	if (!gameObject)
	{
		return;
	}

	auto it = std::find_if(m_rootGameObjects.begin(), m_rootGameObjects.end(),
		[gameObject](const std::shared_ptr<GameObject>& obj)
		{
			return obj == gameObject;
		});

	if (it != m_rootGameObjects.end())
	{
		m_deadObjects.push_back(std::weak_ptr<GameObject>(*it));
	}
	
}

void Scene::removeAll()
{
	end();
	m_deadObjects.clear();
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

	//for the remaining game objects,run down their hierarchy and handle transfers / removals
	for (const auto& object : m_rootGameObjects)
	{
		object->processTransfers();
		object->processComponentRemovals();
	}

	//Handle transfers from the scene to game objects
	processObjectReleases();
}

void Scene::queueObjectRelease(const std::shared_ptr<GameObject>& child, const std::shared_ptr<GameObject>& newParent)
{
	m_childrenToTransfer.push_back({ child, newParent });
}


void Scene::processObjectReleases()
{
	for (auto& request : m_childrenToTransfer)
	{
		auto childPtr = request.child.lock();
		auto newParentPtr = request.newParent.lock();

		if (childPtr)
		{

			auto it = std::find(m_rootGameObjects.begin(), m_rootGameObjects.end(), childPtr);
			const bool isRootObject = (it != m_rootGameObjects.end());
			
			if (newParentPtr)
			{
				if (isRootObject)
				{
					m_rootGameObjects.erase(it);
				}

				newParentPtr->addChild(childPtr); 
			}

		}
	}
	m_childrenToTransfer.clear();
}



void Scene::processGameObjectRemovals()
{
	for (auto& weakObjToRemove : m_deadObjects)
	{
		if (auto sharedObjToRemove = weakObjToRemove.lock())
		{
			auto removeIt = std::remove_if(m_rootGameObjects.begin(), m_rootGameObjects.end(),
				[&sharedObjToRemove](const std::shared_ptr<GameObject>& obj)
				{
					return obj == sharedObjToRemove;
				});

			if (removeIt != m_rootGameObjects.end())
			{
				
				(*removeIt)->end();
				m_rootGameObjects.erase(removeIt, m_rootGameObjects.end());
			}
		}
	}
	m_deadObjects.clear();
}


