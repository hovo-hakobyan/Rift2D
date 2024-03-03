#pragma once
#include "Transform.h"
#include "Interfaces.h"
#include "Renderer.h"
#include "BaseComponent.h"

namespace rift2d
{

	struct ParentChangeRequest
	{
		std::weak_ptr<GameObject> child;
		std::weak_ptr<GameObject> newParent;
	};

	class Texture2D;
	class Scene;
	class GameObject final: public std::enable_shared_from_this<GameObject>
	{
		Transform m_transform{};
		
		std::vector<std::unique_ptr<BaseComponent>> m_components;
		std::vector<BaseComponent*> m_deadComponents;
		static bool m_gameStarted;

		std::vector<std::shared_ptr<GameObject>> m_children;
		std::weak_ptr<GameObject> m_pParent;
		std::vector<ParentChangeRequest> m_transferQueue;

		Scene* m_pScene;

		bool isValidParent(GameObject* pNewParent) const;
		void queueParentTransfer(const std::shared_ptr<GameObject>& child, const std::shared_ptr<GameObject>& newParent);
		void RemoveChild(std::shared_ptr<GameObject> child);
	

	public:
		void init() const;
		void update() const;
		void lateUpdate() const;
		void end();
		

		void setOwningScene(Scene* pScene);

		Transform& getTransform() { return m_transform; }
		const Transform& getTransform() const { return m_transform; }

		GameObject() = default;
		~GameObject() = default;
		GameObject(const GameObject& other) = delete;
		GameObject(GameObject&& other) = delete;
		GameObject& operator=(const GameObject& other) = delete;
		GameObject& operator=(GameObject&& other) = delete;

		void processComponentRemovals();
		void processTransfers();
		void setParent(const std::shared_ptr<GameObject>& pNewParent);

		void addChild(const std::shared_ptr<GameObject>& childToAdd);
		
		std::shared_ptr<GameObject> getParent() const { return m_pParent.lock(); };


		/// <summary>
	/// Adds a component to the GameObject.
	/// </summary>
	/// <remarks>
	/// This function template adds a component of type ComponentType to the GameObject. If a component is added at runtime, init() on the
	///	component is called automatically
	/// </remarks>
	/// <typeparam name="ComponentType">The type of the component to be added. Must be derived from BaseComponent.</typeparam>
	/// <param name="args">Arguments to forward to the ComponentType constructor.</param>
	/// <returns>A pointer to the newly added component.</returns>
		template<typename Component, typename... Args>
		Component* addComponent(Args&&... args)
		{
			static_assert(std::is_base_of<BaseComponent, Component>::value, "Component must derive from BaseComponent");
		

			auto component = std::make_unique<Component>(this, std::forward<Args>(args)...);
			auto rawPtr = component.get();
			if (m_gameStarted)
			{
				component->init();
			}

			m_components.push_back(std::move(component));

			if constexpr (std::is_base_of<IRenderable, Component>::value)
			{
				auto renderableComponent = static_cast<IRenderable*>(rawPtr);
				Renderer::GetInstance().registerComponent(renderableComponent);
				
			}
			
			return rawPtr;
		}

		/// <summary>
/// Retrieves the first component of the specified type from the GameObject.
/// </summary>
/// <remarks>
/// This function searches through the GameObject's components and returns the first component that matches the specified type. 
/// It uses dynamic_cast so avoid calling this function from hot code path.
/// If no component of the specified type is found, nullptr is returned.
/// </remarks>
/// <typeparam name="ComponentType">The type of the component to retrieve. Must be derived from BaseComponent.</typeparam>
/// <returns>A pointer to the component of type ComponentType if found; otherwise, nullptr.</returns>
		template<typename ComponentType>
		ComponentType* getComponent() const
		{
			static_assert(std::is_base_of<BaseComponent, ComponentType>::value, "ComponentType must derive from BaseComponent");

			for (const auto& comp : m_components)
			{
				auto castedComp = dynamic_cast<ComponentType*>(comp.get());
				if (castedComp)
				{
					return castedComp;
				}
			}
			
			return nullptr;
			
		}

		/// <summary>
/// Marks a component of the specified type for deferred removal from the GameObject.
/// </summary>
/// <remarks>
/// This function searches for the first component of the specified type and marks it for removal. 
/// The actual removal of the component is deferred to a later stage to  
/// avoid modifying the component collection during update cycles. 
/// If the component is already marked for removal or not found, this function has no effect.
/// </remarks>
/// <typeparam name="ComponentType">The type of the component to mark for removal. Must derive from BaseComponent.</typeparam>
		template<typename ComponentType>
		void removeComponent()
		{
			static_assert(std::is_base_of<BaseComponent, ComponentType>::value, "ComponentType must derive from BaseComponent");

			auto componentToRemove = getComponent<ComponentType>();
			if (!componentToRemove|| componentToRemove->isMarkedForRemoval())
			{
				return;
			}

			componentToRemove->markForRemoval();
			m_deadComponents.push_back(componentToRemove);
					
		}

		/// <summary>
/// Marks a specific component for deferred removal based on a provided pointer.
/// </summary>
/// <remarks>
/// Given a pointer to a component of type ComponentType, this function marks the component for removal if it is part of the GameObject.
///The actual removal of the component is deferred to a later stage to
/// avoid modifying the component collection during update cycles. 
/// If the component is already marked for removal or not found, this function has no effect.
/// </remarks>
/// <typeparam name="ComponentType">The type of the component to be removed. This type must derive from BaseComponent.</typeparam>
/// <param name="componentToRemove">Pointer to the component of type ComponentType to be marked for removal.</param>
		template<typename ComponentType>
		void removeComponent(ComponentType* componentToRemove)
		{
			static_assert(std::is_base_of<BaseComponent, ComponentType>::value, "ComponentType must derive from BaseComponent");
			
			if (componentToRemove->isMarkedForRemoval() || !componentToRemove)
			{
				return;
			}

			auto it = std::find_if(m_components.begin(), m_components.end(),
				[componentToRemove](const std::unique_ptr<BaseComponent>& component)
				{
					return component.get() == componentToRemove;
				});

				if (it != m_components.end())
				{
					componentToRemove->markForRemoval();
					m_deadComponents.push_back(componentToRemove);
				}
			
		}

		
		
			
	};
}
