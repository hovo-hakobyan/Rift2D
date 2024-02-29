#pragma once
#include "SceneManager.h"
#include "GameObject.h"

namespace rift2d
{
	class Scene final
	{
		friend Scene& SceneManager::CreateScene(const std::string& name);
	public:
		GameObject* Add(std::unique_ptr<GameObject> object);
		void Remove(GameObject* object);
		void RemoveAll();

		void Init();
		void Update();
		void LateUpdate();
		

		~Scene();
		Scene(const Scene& other) = delete;
		Scene(Scene&& other) = delete;
		Scene& operator=(const Scene& other) = delete;
		Scene& operator=(Scene&& other) = delete;

	private: 
		explicit Scene(const std::string& name);

		std::string m_name;
		std::vector <std::unique_ptr<GameObject>> m_objects{};
		std::vector <GameObject*> m_DeadObjects{};

		static unsigned int m_idCounter; 

		void ProcessGameObjectRemovals();
	};

}
