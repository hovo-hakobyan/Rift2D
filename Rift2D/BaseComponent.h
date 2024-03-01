#pragma once
#include "Interfaces.h"
#include <string>
#include <memory>
#include <list>

namespace rift2d
{
	class NullOwnerException
	{
	public:
		NullOwnerException(const std::string& message): m_Message{message}{}

		const std::string& What() const { return m_Message; }

	private:
		std::string m_Message{};
	};

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
		virtual void End() {}

		void MarkForRemoval() { m_IsMarkedForRemoval = true; }
		bool IsMarkedForRemoval() const { return m_IsMarkedForRemoval; }

		void RegisterWatcher(IComponentWatcher* watcher) { m_Watchers.push_back(watcher); }
		void UnregisterWatcher(IComponentWatcher* watcher) { m_Watchers.remove(watcher); }

		void NotifyRemoval()
		{
			if (m_Watchers.empty())
			{
				return;
			}

			for (auto* watcher : m_Watchers)
			{
				watcher->OnComponentRemoved(this);
			}
		}

	protected:
		BaseComponent(GameObject* owner) : m_pOwner{ owner }
		{
			if (!owner)
			{
				throw NullOwnerException("BaseComponent must have a non-null owner");
			}
		}
		GameObject* GetParent() const { return m_pOwner; }
	private:
		bool m_IsMarkedForRemoval{};
		GameObject* m_pOwner;
		std::list<IComponentWatcher*> m_Watchers;
		
	};

}

