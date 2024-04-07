#pragma once
#include "GameObject.h"
#include "Prefab.h"
#include "Transform.h"

namespace rift2d
{
	template<typename T>
	concept IsPrefab = std::is_base_of_v<Prefab, T>;

	class Scene
	{
	public:
		GameObject* addGameObject(std::unique_ptr<GameObject> object);
		GameObject* createGameObject();

		template<IsPrefab DerivedPrefab>
		GameObject* addGameObjectFromPrefab(const glm::vec3& loc = {0,0,1})
		{
			auto go = std::make_unique<GameObject>(this);
			go->getTransform()->setLocalPosition(loc);
			auto rawPtr = go.get();
			addGameObject(std::move(go));
			auto pfab = std::make_unique<DerivedPrefab>();
			pfab->setup(rawPtr, this);
			return rawPtr;

		}

		void remove(GameObject* object);
		void removeAll();
		std::unique_ptr<GameObject> releaseGameObject(GameObject* go);

		bool isInitialized() const { return m_isInitialized; }
		std::string getName() const { return m_name; }

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
