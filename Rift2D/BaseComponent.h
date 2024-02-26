#pragma once
#include "Interfaces.h"
#include <memory>

namespace rift2d
{
	class GameObject;
	class BaseComponent
	{
	public:
		friend class GameObject;

		virtual ~BaseComponent() = default;
		BaseComponent(const BaseComponent& other) = delete;
		BaseComponent(BaseComponent&& other) = delete;
		BaseComponent& operator=(const BaseComponent& other) = delete;
		BaseComponent& operator=(BaseComponent&& other) = delete;
		
		virtual void Init() = 0;
		virtual void Update() = 0;

		void MarkForRemoval() { m_IsMarkedForRemoval = true; }
		bool IsMarkedForRemoval() const { return m_IsMarkedForRemoval; }

		
	protected:
		std::weak_ptr<GameObject> m_Owner;
		BaseComponent(std::shared_ptr<GameObject> owner) : m_Owner{ owner }{}
		bool m_IsMarkedForRemoval{};
		
	};

}

