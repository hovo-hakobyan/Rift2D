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
		virtual void Update() {}
		virtual void FixedUpdate() {}

		
	protected:
		std::weak_ptr<GameObject> m_Owner;
		BaseComponent(std::shared_ptr<GameObject> owner) : m_Owner{ owner }{}

		
	};

}

