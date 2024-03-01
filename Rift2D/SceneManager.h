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
		void init();
		void update();
		void lateUpdate();
		void end();
	private:
		friend class Singleton<SceneManager>;
		SceneManager();
		std::vector<std::unique_ptr<Scene>> m_scenes;
	};
}
