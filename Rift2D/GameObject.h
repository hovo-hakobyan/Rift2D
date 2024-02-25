#pragma once
#include <string>
#include "Transform.h"
#include "Interfaces.h"
#include "Renderer.h"
#include "BaseComponent.h"

namespace rift2d
{
	class Texture2D;
	class GameObject final: public std::enable_shared_from_this<GameObject>
	{
		Transform m_transform{};
		
		std::vector<std::shared_ptr<BaseComponent>> m_Components;
		std::vector<std::shared_ptr<BaseComponent>> m_ComponentsToAdd;
		std::vector<std::shared_ptr<BaseComponent>> m_DeadComponents;

	public:
		void Init();
		void Update();

		Transform& GetTransform() { return m_transform; }
		const Transform& GetTransform() const { return m_transform; }

		GameObject() = default;
		virtual ~GameObject();
		GameObject(const GameObject& other) = delete;
		GameObject(GameObject&& other) = delete;
		GameObject& operator=(const GameObject& other) = delete;
		GameObject& operator=(GameObject&& other) = delete;


		template<typename Component, typename... Args>
		std::shared_ptr<Component> AddComponent(Args&&... args)
		{
			static_assert(std::is_base_of<BaseComponent, Component>::value, "Component must derive from BaseComponent");
			

			auto component = std::make_shared<Component>(shared_from_this(), std::forward<Args>(args)...);
			m_Components.push_back(component);

			if constexpr (std::is_base_of<IRenderable, Component>::value)
			{
				auto renderableComponent = std::static_pointer_cast<IRenderable>(component);
				Renderer::GetInstance().RegisterComponent(renderableComponent);
			}
			
			return component;
		}

		template<typename ComponentType>
		std::shared_ptr<ComponentType> GetComponent() const
		{
			static_assert(std::is_base_of<BaseComponent, ComponentType>::value, "ComponentType must derive from BaseComponent");

			for (const auto& comp : m_Components)
			{
				auto castedComp = std::dynamic_pointer_cast<ComponentType>(comp);
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
		void RemoveComponent(const std::shared_ptr<ComponentType>& componentToRemove)
		{
			static_assert(std::is_base_of<BaseComponent, ComponentType>::value, "ComponentType must derive from BaseComponent");
			
			if (componentToRemove->IsMarkedForRemoval())
			{
				return;
			}

			auto exists = std::find_if(m_Components.begin(), m_Components.end(),
				[&componentToRemove](const std::shared_ptr<BaseComponent>& component)
				{
					return component == componentToRemove;
				}) != m_Components.end();

				if (exists)
				{
					componentToRemove->MarkForRemoval();
					m_DeadComponents.push_back(componentToRemove);
				}
			
		}

		void ProcessRemovals()
		{
			for (const auto& compToRemove : m_DeadComponents)
			{
				auto it = std::remove(m_Components.begin(), m_Components.end(), compToRemove);
				if (it != m_Components.end())
				{
					m_Components.erase(it, m_Components.end());

					// Unregister from Renderer if it's renderable
					auto renderableComponent = std::dynamic_pointer_cast<IRenderable>(compToRemove);
					if (renderableComponent)
					{
						Renderer::GetInstance().UnregisterComponent(renderableComponent);
					}
				}
			}

			m_DeadComponents.clear();
		}
			
	};
}
