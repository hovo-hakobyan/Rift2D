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
		explicit NullOwnerException(std::string message): m_message{std::move(message)}{}

		const std::string& what() const { return m_message; }

	private:
		std::string m_message{};
	};

	class GameObject;
	class BaseComponent
	{
	public:

		explicit BaseComponent(GameObject* owner) : m_pOwner{ owner }
		{
			if (!owner)
			{
				throw NullOwnerException("BaseComponent must have a non-null owner");
			}
		}

		virtual ~BaseComponent() = default;
		BaseComponent(const BaseComponent& other) = delete;
		BaseComponent(BaseComponent&& other) = delete;
		BaseComponent& operator=(const BaseComponent& other) = delete;
		BaseComponent& operator=(BaseComponent&& other) = delete;
		
		virtual void init() { m_isInitialized = true; }
		virtual void fixedUpdate() {}
		virtual void update() {}
		virtual void lateUpdate() {}
		virtual void end() { m_isInitialized = false; }
		virtual void onImGui(){}

		void markForRemoval() { m_isMarkedForRemoval = true; }
		bool isMarkedForRemoval() const { return m_isMarkedForRemoval; }
		bool isInitialized() const { return m_isInitialized; }
		bool isDisabled() const { return m_isDisabled; }
		void disable() { m_isDisabled = true; }
		void enable() { m_isDisabled = false; }

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
		GameObject* getOwner() const { return m_pOwner; }
	private:
		bool m_isMarkedForRemoval{};
		bool m_isDisabled{};
		GameObject* m_pOwner;
		std::list<IComponentWatcher*> m_watchers;
		bool m_isInitialized{ false };
		
	};

}

