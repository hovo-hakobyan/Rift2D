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
		Scene& CreateScene(const std::string& name);
		~SceneManager();
		void Init();
		void Update();
		void LateUpdate();
	private:
		friend class Singleton<SceneManager>;
		SceneManager();
		std::vector<std::unique_ptr<Scene>> m_scenes;
	};
}
