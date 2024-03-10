#pragma once
#include <vector>
#include <string>
#include <memory>
#include "Singleton.h"

namespace rift2d
{
	class Scene;
	class SceneManager final : public Singleton<SceneManager>
	{
	public:
		Scene& createScene(const std::string& name);
		~SceneManager();
		void init() const;
		void update() const;
		void lateUpdate() const;
		void end() const;
		void onImGui() const;
		void frameCleanup() const;

		Scene* GetCurrentScene() const { return m_scenes[m_currentSceneIdx].get(); } 
	private:
		friend class Singleton<SceneManager>;
		SceneManager();
		std::vector<std::unique_ptr<Scene>> m_scenes;
		int m_currentSceneIdx{-1};
	};
}
