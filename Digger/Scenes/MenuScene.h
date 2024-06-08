#pragma once
#include "Scene.h"

namespace digger
{
	class DiggerGameMode;
	class MenuScene : public rift2d::Scene
	{
	public:
		MenuScene();
		~MenuScene() override = default;
		MenuScene(const MenuScene& other) = delete;
		MenuScene(MenuScene&& other) noexcept = delete;
		MenuScene& operator=(const MenuScene& other) = delete;
		MenuScene& operator=(MenuScene&& other) noexcept = delete;

	protected:

		virtual void init() override;
		virtual void onActivate() override;
		virtual void onImGui() override;

	private:
		DiggerGameMode* m_pGameMode{};
	};


}
