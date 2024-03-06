#include "GameObject.h"
#include "ResourceManager.h"
#include "Renderer.h"
#include "BaseComponent.h"
#include "Scene.h"
#include  <ranges>

bool rift2d::GameObject::m_gameStarted{ false };

rift2d::GameObject::GameObject(Scene* pOwner):
	m_pScene{pOwner}
{
	m_transform = addComponent<Transform>();
}

rift2d::GameObject::~GameObject() = default;

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

void rift2d::GameObject::update() 
{
	processComponentCache();

	for (const auto& comp : m_components) 
	{
		comp->update();
	}

	for (const auto& child : m_children)
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

	m_components.clear();
	m_componentsCache.clear();

	for (const auto& child : m_children)
	{
		child->end();
	}
	m_children.clear();

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

void rift2d::GameObject::processGameObjectRemovals()
{
	if (m_isMarkedForDestruction)
	{
		end();
		return;
	}

	// Filter elements that are marked for destruction and call end
	//Invokes IsMarkedForDestruction for each child and if true, invokes end();
	for (const auto& child : m_children | std::views::filter(&GameObject::isMarkedForDestruction))
	{
		child->end();
	}

	m_children.erase(std::remove_if(m_children.begin(), m_children.end(),
		[](const std::unique_ptr<GameObject>& child) { return child->isMarkedForDestruction(); }),
		m_children.end());

	//filter elements that are not marked for destruction
	//Cannot bind function pointer because return is inverted
	for (const auto& child : m_children | std::views::filter([](const auto& child) { return !child->isMarkedForDestruction(); }))
	{
		child->processGameObjectRemovals();
	}

}

void rift2d::GameObject::setParent(GameObject* pParent, bool keepWorldPosition)
{
	if (!isValidParent(pParent) or m_pParent == pParent) return;

	//Is root object
	if(pParent == nullptr)
	{
		//local == world because no parent
		m_transform->setLocalPosition(m_transform->getWorldPosition());
	}
	else
	{
		if(keepWorldPosition)
		{
			m_transform->setLocalPosition(m_transform->getWorldPosition() - pParent->getTransform()->getWorldPosition());
		}
	}

	std::unique_ptr<GameObject> child;
	//Remove from old parent if there is one
	if(m_pParent)
	{
		auto it = std::find_if(m_pParent->m_children.begin(), m_pParent->m_children.end(), [this](const auto& go) {
			return go.get() == this;
			});


		if( it != m_pParent->m_children.end())
		{
			child = std::move(*it);
			m_pParent->m_children.erase(it);
		}
	}

	m_pParent = pParent;

	//add to new parent, if there is one
	if(m_pParent)
	{
		//We had no previous parent
		if(!child)
		{
			child = m_pScene->releaseGameObject(this);
		}
		m_pParent->m_children.push_back(std::move(child));
	}
}


void rift2d::GameObject::markForDestroy()
{
	m_isMarkedForDestruction = true;

	for (const auto& child : m_children) 
	{
		child->markForDestroy();
	}
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

void rift2d::GameObject::processComponentCache()
{
	if(!m_componentsCache.empty())
	{
		std::ranges::move(m_componentsCache, std::back_inserter(m_components));
		m_componentsCache.clear();
		if (m_gameStarted)
		{
			for(const auto& comp : m_components)
			{
				if (!comp->isInitialized()) comp->init();
			}
		}
		
	}

	
}
