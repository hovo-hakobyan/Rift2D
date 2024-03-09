#pragma once
#include "SceneManager.h"
#include "GameObject.h"

namespace rift2d
{
	class Scene final
	{
		friend Scene& SceneManager::createScene(const std::string& name);
		

	public:
		GameObject* add(std::unique_ptr<GameObject> object);
		void remove(GameObject* object);
		void removeAll();
		std::unique_ptr<GameObject> releaseGameObject(GameObject* go);
		

		void init() const;
		void update() const;
		void lateUpdate() const;
		void end() const;
		void frameCleanup() ;

		~Scene();
		Scene(const Scene& other) = delete;
		Scene(Scene&& other) = delete;
		Scene& operator=(const Scene& other) = delete;
		Scene& operator=(Scene&& other) = delete;

	private:
		explicit Scene(std::string name);

		std::string m_name;
		std::vector <std::unique_ptr<GameObject>> m_rootGameObjects{};

		static unsigned int m_idCounter; 

		void processGameObjectRemovals();

	};

}
