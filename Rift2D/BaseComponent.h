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
		
		virtual void Init(){}
		virtual void Update() {}
		virtual void LateUpdate() {}

		void MarkForRemoval() { m_IsMarkedForRemoval = true; }
		bool IsMarkedForRemoval() const { return m_IsMarkedForRemoval; }

	protected:
		BaseComponent(std::shared_ptr<GameObject> owner) : m_Owner{ owner }{}
		std::weak_ptr<GameObject> GetParent() const { return m_Owner; }
	private:
		bool m_IsMarkedForRemoval{};
		std::weak_ptr<GameObject> m_Owner;
		
	};

}

