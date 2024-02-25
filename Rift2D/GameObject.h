#pragma once
#include <string>
#include "Transform.h"
#include "Interfaces.h"
#include "Renderer.h"

namespace rift2d
{
	class Texture2D;
	class BaseComponent;
	class GameObject final
	{
		Transform m_transform{};
		
		std::vector<std::shared_ptr<BaseComponent>> m_Components;
	public:
		virtual void Update();

		void SetPosition(float x, float y);

		GameObject() = default;
		virtual ~GameObject();
		GameObject(const GameObject& other) = delete;
		GameObject(GameObject&& other) = delete;
		GameObject& operator=(const GameObject& other) = delete;
		GameObject& operator=(GameObject&& other) = delete;

		//Add component for non renderables
		template<typename Component, typename std::enable_if<!std::is_base_of<IRenderable, Component>::value,int>::type = 0>
		void AddComponent(std::unique_ptr<Component> component)
		{
			m_Components.push_back(component);
		}

		//Add component for renderables
		template<typename Component, typename std::enable_if<std::is_base_of<IRenderable, Component>::value, int>::type = 0>
		void AddComponent(std::shared_ptr<Component> component)
		{
			m_Components.push_back(component);

			auto renderableComponent = std::static_pointer_cast<IRenderable>(component);
			Renderer::GetInstance().RegisterComponent(component);
		}
	};
}
