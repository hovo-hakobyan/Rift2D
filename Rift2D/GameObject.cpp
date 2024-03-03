#include <string>
#include "GameObject.h"
#include "ResourceManager.h"
#include "Renderer.h"
#include "BaseComponent.h"
#include "Scene.h"

bool rift2d::GameObject::m_gameStarted{ false };



void rift2d::GameObject::init() const
{
	for (auto& comp : m_components)
	{
		comp->init();
	}

	for(auto& child : m_children)
	{
		child->init();
	}

	m_gameStarted = true;
}

void rift2d::GameObject::update() const
{
	for (auto& comp : m_components) 
	{
		comp->update();
	}

	for (auto& child : m_children)
	{
		child->update();
	}
}

void rift2d::GameObject::lateUpdate() const
{
	for (auto& comp : m_components)
	{
		comp->lateUpdate();
	}

	for (auto& child : m_children)
	{
		child->lateUpdate();
	}


}

void rift2d::GameObject::end() 
{
	auto& renderer = Renderer::GetInstance();
	for (auto& comp : m_components)
	{
		//if renderable, unregister from the renderer
		IRenderable* renderableComp = dynamic_cast<IRenderable*>(comp.get());
		if (renderableComp)
		{
			renderer.unregisterComponent(renderableComp);
		}

		comp->end();
	}

	for (auto& child : m_children)
	{
		child->end();
	}
}

void rift2d::GameObject::setOwningScene(Scene* pScene)
{
	m_pScene = pScene;
}

void rift2d::GameObject::processComponentRemovals()
{
	for (auto* compToRemove : m_deadComponents)
	{
		// Unregister from Renderer if it's renderable
		if (auto* renderable = dynamic_cast<IRenderable*>(compToRemove))
		{
			Renderer::GetInstance().unregisterComponent(renderable);
		}

		compToRemove->notifyRemoval();
		compToRemove->end();

		m_components.erase(std::remove_if(m_components.begin(), m_components.end(),
			[compToRemove](const std::unique_ptr<BaseComponent>& componentPtr) {
				return componentPtr.get() == compToRemove;
			}),
			m_components.end());

	}
	m_deadComponents.clear();

	for(const auto& child : m_children)
	{
		child->processComponentRemovals();
	}
}

void rift2d::GameObject::setParent(const std::shared_ptr<GameObject>& pNewParent)
{
	const auto currentParent = m_pParent.lock();
	//The new parent is not a valid candidate
	if (pNewParent == currentParent or !isValidParent(pNewParent.get())) return;

	//Nullptr passed, means detach from parent
	//Destroy since you cannot exist without parent
	if(!pNewParent)
	{
		if (currentParent)
		{
			currentParent->queueParentTransfer(shared_from_this(), nullptr);
		}
		return;
	}

	if (currentParent) currentParent->queueParentTransfer(shared_from_this(), pNewParent);
	else if (m_pScene) m_pScene->queueObjectRelease(shared_from_this(), pNewParent);
}

void rift2d::GameObject::addChild(const std::shared_ptr<GameObject>& childToAdd)
{
	if (!childToAdd) return;

	// Add to this object's children
	m_children.push_back(childToAdd);
	childToAdd->m_pParent = shared_from_this();
}

bool rift2d::GameObject::isValidParent(GameObject* pNewParent) const
{
	if (pNewParent == this) return false;

	//If none of the children (and their children) are the new parent, it is a valid parent
	return std::ranges::none_of(m_children, [pNewParent](const auto& child)
		{
			return child.get() == pNewParent or child->isValidParent(pNewParent);
		});

}

void rift2d::GameObject::queueParentTransfer(const std::shared_ptr<GameObject>& child,
	const std::shared_ptr<GameObject>& newParent)
{
	m_transferQueue.push_back({ child,newParent });
}

void rift2d::GameObject::RemoveChild(std::shared_ptr<GameObject> child)
{
	m_children.erase(std::remove_if(m_children.begin(), m_children.end(),
		[&child](const std::shared_ptr<GameObject>& obj)
		{
			return obj == child;
		}), m_children.end());
	child->m_pParent.reset(); // Remove parent reference
}





void rift2d::GameObject::processTransfers()
{
	for (auto& request : m_transferQueue)
	{
		auto childPtr = request.child.lock();
		auto newParentPtr = request.newParent.lock();

		if (childPtr)
		{
			// Check if the child still exists
			// If newParentPtr is expired, it means either no parent was specified (root level)
			// or the new parent was destroyed before the transfer could be processed.
			if (newParentPtr)
			{
				//transfer to new parent
				//remove from old parent
				//set the new parent to its parent
				newParentPtr->RemoveChild(childPtr);
				newParentPtr->addChild(childPtr);
			}
			else
			{
				if(m_pScene)
				{
					RemoveChild(childPtr);
					m_pScene->add(childPtr);
				}
			}
			
		}
	}
	m_transferQueue.clear();

	// Recursively process transfers for all remaining children
	for (const auto& child : m_children) 
	{
		child->processTransfers();
	}
}
