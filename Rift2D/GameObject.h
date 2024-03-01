#pragma once
#include "Transform.h"
#include "Interfaces.h"
#include "Renderer.h"
#include "BaseComponent.h"

namespace rift2d
{
	class Texture2D;
	class GameObject final
	{
		Transform m_transform{};
		
		std::vector<std::unique_ptr<BaseComponent>> m_Components;
		std::vector<BaseComponent*> m_DeadComponents;
		static bool m_GameStarted;

	public:
		void Init();
		void Update();
		void LateUpdate();
		void End();

		Transform& GetTransform() { return m_transform; }
		const Transform& GetTransform() const { return m_transform; }

		GameObject() = default;
		~GameObject() = default;
		GameObject(const GameObject& other) = delete;
		GameObject(GameObject&& other) = delete;
		GameObject& operator=(const GameObject& other) = delete;
		GameObject& operator=(GameObject&& other) = delete;


		template<typename Component, typename... Args>
		Component* AddComponent(Args&&... args)
		{
			static_assert(std::is_base_of<BaseComponent, Component>::value, "Component must derive from BaseComponent");
		

			auto component = std::make_unique<Component>(this, std::forward<Args>(args)...);
			auto rawPtr = component.get();
			if (m_GameStarted)
			{
				component->Init();
			}

			m_Components.push_back(std::move(component));

			if constexpr (std::is_base_of<IRenderable, Component>::value)
			{
				auto renderableComponent = static_cast<IRenderable*>(rawPtr);
				Renderer::GetInstance().RegisterComponent(renderableComponent);
			}
			
			return rawPtr;
		}

		template<typename ComponentType>
		ComponentType* GetComponent() const
		{
			static_assert(std::is_base_of<BaseComponent, ComponentType>::value, "ComponentType must derive from BaseComponent");

			for (const auto& comp : m_Components)
			{
				auto castedComp = dynamic_cast<ComponentType*>(comp.get());
				if (castedComp)
				{
					return castedComp;
				}
			}
			
			return nullptr;
			
		}

		/**
		* @brief Marks a component for removal.
		*
		* This function marks a component of type ComponentType for deferred removal.
		*
		* @tparam ComponentType The type of the component to remove.
		*/
		template<typename ComponentType>
		void RemoveComponent()
		{
			static_assert(std::is_base_of<BaseComponent, ComponentType>::value, "ComponentType must derive from BaseComponent");

			auto componentToRemove = GetComponent<ComponentType>();
			if (!componentToRemove|| componentToRemove->IsMarkedForRemoval())
			{
				return;
			}

			componentToRemove->MarkForRemoval();
			m_DeadComponents.push_back(componentToRemove);
					
		}

		/**
		* @brief Marks a component for removal.
		*
		* This function marks a component of type ComponentType for deferred removal.
		*
		* @tparam ComponentType The type of the component to remove.
		*/
		template<typename ComponentType>
		void RemoveComponent(ComponentType* componentToRemove)
		{
			static_assert(std::is_base_of<BaseComponent, ComponentType>::value, "ComponentType must derive from BaseComponent");
			
			if (componentToRemove->IsMarkedForRemoval() || !componentToRemove)
			{
				return;
			}

			auto it = std::find_if(m_Components.begin(), m_Components.end(),
				[componentToRemove](const std::unique_ptr<BaseComponent>& component)
				{
					return component.get() == componentToRemove;
				});

				if (it != m_Components.end())
				{
					componentToRemove->MarkForRemoval();
					m_DeadComponents.push_back(componentToRemove);
				}
			
		}

		void ProcessRemovals()
		{
			for ( auto* compToRemove : m_DeadComponents)
			{
				// Unregister from Renderer if it's renderable
				if (auto* renderable = dynamic_cast<IRenderable*>(compToRemove))
				{
					Renderer::GetInstance().UnregisterComponent(renderable);
				}

				compToRemove->NotifyRemoval();
				compToRemove->End();

				m_Components.erase(std::remove_if(m_Components.begin(), m_Components.end(),
					[compToRemove](const std::unique_ptr<BaseComponent>& componentPtr) {
						return componentPtr.get() == compToRemove;
					}),
					m_Components.end());

			}

			m_DeadComponents.clear();
		}
			
	};
}
