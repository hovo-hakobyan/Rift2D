#pragma once
#include "Scene.h"

namespace rift2d
{
	class MenuScene : public Scene
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
	};


}
