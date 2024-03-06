#pragma once
#include "Transform.h"
#include "Interfaces.h"
#include "Renderer.h"
#include "BaseComponent.h"

namespace rift2d
{

	class Texture2D;
	class Scene;
	class GameObject final
	{
		Transform* m_transform;
		
		std::vector<std::unique_ptr<BaseComponent>> m_components;
		std::vector<std::unique_ptr<BaseComponent>> m_componentsCache;
		std::vector<BaseComponent*> m_deadComponents;
		static bool m_gameStarted;

		std::vector<std::unique_ptr<GameObject>> m_children{};
		GameObject* m_pParent{};
		bool m_isMarkedForDestruction{false};

		Scene* m_pScene;

		bool isValidParent(GameObject* pNewParent) const;

	public:
		void init() const;
		void update();
		void lateUpdate() const;
		void end();

		Transform* getTransform() { return m_transform; }
		const Transform* getTransform() const { return m_transform; }

		GameObject(Scene* pOwner);
		~GameObject();
		GameObject(const GameObject& other) = delete;
		GameObject(GameObject&& other) = delete;
		GameObject& operator=(const GameObject& other) = delete;
		GameObject& operator=(GameObject&& other) = delete;

		void processComponentRemovals();
		void processGameObjectRemovals();
		void processComponentCache();

		void setParent(GameObject* pParent, bool keepWorldPosition);
		
		GameObject* getParent() const { return m_pParent; };
		const std::vector<std::unique_ptr<GameObject>>& getChildren() const { return m_children; }

		void markForDestroy();
		bool isMarkedForDestruction()const { return m_isMarkedForDestruction; }

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

			if constexpr (std::is_base_of<IRenderable, Component>::value)
			{
				auto renderableComponent = static_cast<IRenderable*>(rawPtr);
				Renderer::GetInstance().registerComponent(renderableComponent);
			}

			m_componentsCache.push_back(std::move(component));
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
