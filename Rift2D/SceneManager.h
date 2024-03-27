#pragma once
#include <vector>
#include <memory>
#include "Singleton.h"

namespace rift2d
{
	class Scene;
	class SceneManager final : public Singleton<SceneManager>
	{
	public:
		Scene* addScene(std::unique_ptr<Scene> scene);
		~SceneManager() override;
		void init() const;
		void update() const;
		void lateUpdate() const;
		void end() const;
		void onImGui() const;
		void frameCleanup();

		Scene* getActiveScene() const { return m_scenes[m_activeSceneIdx].get(); }
		void setActiveScene(int sceneIdx);
	private:
		friend class Singleton<SceneManager>;
		SceneManager();
		std::vector<std::unique_ptr<Scene>> m_scenes;
		int m_activeSceneIdx{-1};
		int m_newSceneIdx{};
		bool m_shouldSwapScene{};
	};
}
