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

		void init();
		void update();
		void lateUpdate();
		void end();
		

		~Scene();
		Scene(const Scene& other) = delete;
		Scene(Scene&& other) = delete;
		Scene& operator=(const Scene& other) = delete;
		Scene& operator=(Scene&& other) = delete;

	private: 
		explicit Scene(const std::string& name);

		std::string m_name;
		std::vector <std::unique_ptr<GameObject>> m_objects{};
		std::vector <GameObject*> m_deadObjects{};

		static unsigned int m_idCounter; 

		void processGameObjectRemovals();
	};

}
