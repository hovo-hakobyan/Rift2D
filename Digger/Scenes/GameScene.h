#pragma once
#include <Scene.h>
namespace digger
{
	class GameScene :public rift2d::Scene
	{
	public:
		GameScene(int level);
		~GameScene() override = default;
		GameScene(const GameScene& other) = delete;
		GameScene(GameScene&& other) noexcept = delete;
		GameScene& operator=(const GameScene& other) = delete;
		GameScene& operator=(GameScene&& other) noexcept = delete;

	protected:
		virtual void init() override;
		virtual void end() override;

	private:
		int m_levelIdx{};
		rift2d::ICommand* m_shootCommand{};
	};

}

