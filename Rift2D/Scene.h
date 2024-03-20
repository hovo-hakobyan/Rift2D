#pragma once
#include "SceneManager.h"
#include "GameObject.h"

namespace rift2d
{
	class Scene
	{
	public:
		GameObject* add(std::unique_ptr<GameObject> object);
		void remove(GameObject* object);
		void removeAll();
		std::unique_ptr<GameObject> releaseGameObject(GameObject* go);

		bool isInitialized() const { return m_isInitialized; }

		virtual ~Scene();
		Scene(const Scene& other) = delete;
		Scene(Scene&& other) = delete;
		Scene& operator=(const Scene& other) = delete;
		Scene& operator=(Scene&& other) = delete;

	protected:
		explicit Scene(std::string name);

		virtual void init() = 0;
		virtual void update() {}
		virtual void lateUpdate() {}
		virtual void end() {}
		virtual void onImGui() {}
	private:
		friend class SceneManager;

		std::string m_name;
		std::vector <std::unique_ptr<GameObject>> m_rootGameObjects{};
		bool m_isInitialized{ false };
		static unsigned int m_idCounter; 
		void processGameObjectRemovals();

		void rootInit();
		void rootUpdate() ;
		void rootLateUpdate() ;
		void rootEnd() ;
		void rootOnImGui() ;
		void rootFrameCleanup();

	};

}
