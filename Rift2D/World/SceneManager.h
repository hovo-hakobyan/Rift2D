#pragma once
#include <memory>
#include <string>
#include <unordered_map>

#include "Singleton.h"

namespace rift2d
{
	class Scene;
	class SceneManager final : public Singleton<SceneManager>
	{
	public:
		Scene* addScene(std::unique_ptr<Scene> scene);
		~SceneManager() override;
		void init();
		void fixedUpdate();
		void update() const;
		void lateUpdate() const;
		void end() const;
		void onImGui() const;
		void frameCleanup();

		Scene* getActiveScene() const;
		void setActiveScene(const std::string& sceneName, bool destroyCurrentScene = false);
		bool isValidScene(const std::string& sceneName) const;
	private:
		friend class Singleton<SceneManager>;
		SceneManager();
		std::unordered_map<std::string, std::unique_ptr<Scene>> m_scenes;
		std::unique_ptr<Scene> m_pActiveScene;
		std::unique_ptr<Scene> m_pNextScene;
		bool m_destroyCurrentScene;
	};
}
