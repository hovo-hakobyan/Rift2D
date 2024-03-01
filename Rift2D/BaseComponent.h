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
		explicit NullOwnerException(const std::string& message): m_message{message}{}

		const std::string& what() const { return m_message; }

	private:
		std::string m_message{};
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
		
		virtual void init(){}
		virtual void update() {}
		virtual void lateUpdate() {}
		virtual void end() {}

		void markForRemoval() { m_isMarkedForRemoval = true; }
		bool isMarkedForRemoval() const { return m_isMarkedForRemoval; }

		void registerWatcher(IComponentWatcher* watcher) { m_watchers.push_back(watcher); }
		void unregisterWatcher(IComponentWatcher* watcher) { m_watchers.remove(watcher); }

		void notifyRemoval()
		{
			if (m_watchers.empty())
			{
				return;
			}

			for (auto* watcher : m_watchers)
			{
				watcher->onComponentRemoved(this);
			}
		}

	protected:
		explicit BaseComponent(GameObject* owner) : m_pOwner{ owner }
		{
			if (!owner)
			{
				throw NullOwnerException("BaseComponent must have a non-null owner");
			}
		}
		GameObject* getParent() const { return m_pOwner; }
	private:
		bool m_isMarkedForRemoval{};
		GameObject* m_pOwner;
		std::list<IComponentWatcher*> m_watchers;
		
	};

}

