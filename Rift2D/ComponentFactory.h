#pragma once
#include <functional>
#include <memory>
#include <BaseComponent.h>
#include "GameObject.h"

namespace rift2d
{
	class ComponentFactory
	{
	public:
		using CreatorFunc = std::function<std::shared_ptr<BaseComponent>(std::shared_ptr<GameObject>)>;

	private:
		std::unordered_map<std::string, CreatorFunc> m_Creators;

	public:
		template<typename ComponentType>
		void RegisterComponent(const std::string& componentName)
		{
			m_Creators[componentName] = [](std::shared_ptr<GameObject> owner) -> std::shared_ptr<BaseComponent>
				{
					return std::static_pointer_cast<BaseComponent>(std::make_shared<ComponentType>(owner));
				}
		}

		std::shared_ptr<BaseComponent> CreateComponent(const std::string& componentName, std::shared_ptr<GameObject> owner)
		{
			auto it = m_Creators.find(componentName);
			if (it != m_Creators.end())
			{
				return it->second(owner);
			}

			return nullptr;
		}
	};
}