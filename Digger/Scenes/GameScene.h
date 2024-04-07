#pragma once
#include <Scene.h>
namespace digger
{
	class GameScene :public rift2d::Scene
	{
	public:
		GameScene();
		~GameScene() override = default;
		GameScene(const GameScene& other) = delete;
		GameScene(GameScene&& other) noexcept = delete;
		GameScene& operator=(const GameScene& other) = delete;
		GameScene& operator=(GameScene&& other) noexcept = delete;

	protected:
		virtual void init() override;
	};

}

