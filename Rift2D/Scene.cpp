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

	gameObject->markForDestroy();

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

	//for the remaining game objects,run down their hierarchy and handle transfers / removals
	for (const auto& object : m_rootGameObjects)
	{
		object->processTransfers();
		object->processComponentRemovals();
	}

	//Handle transfers from the scene to game objects
	processObjectReleases();

	//remove dead game objects
	processGameObjectRemovals();
}

void Scene::queueObjectRelease(const std::shared_ptr<GameObject>& child, const std::shared_ptr<GameObject>& newParent, bool keepWorldPosition)
{
	glm::vec3 worldPositionBeforeChange{0,0,0};
	if (keepWorldPosition)
	{
		worldPositionBeforeChange = child->getTransform()->getWorldPosition();
	}
	m_childrenToTransfer.push_back({ child, newParent,keepWorldPosition,worldPositionBeforeChange });
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

				
				glm::vec3 newLocalPosition{0,0,0};
				const auto childTransform = childPtr->getTransform();
				if (request.keepWorldPosition)
				{
					const auto parentTransform = newParentPtr->getTransform();
					
					if (parentTransform and childTransform)
					{
						newLocalPosition = request.originalWorldPos;
						const glm::vec3 parentWorldPosition = parentTransform->getWorldPosition();
						newLocalPosition -= parentWorldPosition;
						
					}
					
				}
				childTransform->setLocalPosition(newLocalPosition.x, newLocalPosition.y, newLocalPosition.z);

				newParentPtr->addChild(childPtr); 
			}

		}
	}
	m_childrenToTransfer.clear();
}


void Scene::processGameObjectRemovals()
{
	auto predicate = [](const std::shared_ptr<GameObject>& obj)
		{
			return obj->isMarkedForDestruction();
		};

	for (auto it = m_rootGameObjects.begin(); it != m_rootGameObjects.end(); )
	{
		// If GameObject is marked for destruction
		if (predicate(*it))
		{
			// Call end() before removal
			(*it)->end();

			// Remove the GameObject
			it = m_rootGameObjects.erase(it);
		}
		else
		{
			// Recursively check and process child GameObject removals
			(*it)->processChildRemovals();
			++it;
		}
	}
}


