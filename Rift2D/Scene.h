#pragma once
#include "SceneManager.h"
#include "GameObject.h"

namespace rift2d
{
	class Scene final
	{
		friend Scene& SceneManager::createScene(const std::string& name);
		

	public:
		std::weak_ptr<GameObject> add(std::shared_ptr<GameObject> object);
		void remove(const std::shared_ptr<GameObject>& gameObject);
		void removeAll();

		void init() const;
		void update() const;
		void lateUpdate() const;
		void end() const;
		void frameCleanup() ;

		void queueObjectRelease(const std::shared_ptr<GameObject>& child, const std::shared_ptr<GameObject>& newParent);
		void processObjectReleases();
		

		~Scene();
		Scene(const Scene& other) = delete;
		Scene(Scene&& other) = delete;
		Scene& operator=(const Scene& other) = delete;
		Scene& operator=(Scene&& other) = delete;

	private:
		explicit Scene(const std::string& name);

		std::string m_name;
		std::vector <std::shared_ptr<GameObject>> m_rootGameObjects{};
		std::vector <std::weak_ptr<GameObject>> m_deadObjects{};
		std::vector<ParentChangeRequest> m_childrenToTransfer;

		static unsigned int m_idCounter; 

		void processGameObjectRemovals();

	};

}
