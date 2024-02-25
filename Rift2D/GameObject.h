#pragma once
#include <string>
#include "Transform.h"
#include "Interfaces.h"
#include "Renderer.h"

namespace rift2d
{
	class Texture2D;
	class BaseComponent;
	class GameObject final: public std::enable_shared_from_this<GameObject>
	{
		Transform m_transform{};
		
		std::vector<std::shared_ptr<BaseComponent>> m_Components;
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
	};
}
