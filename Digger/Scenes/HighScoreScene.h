#pragma once
#include "Scene.h"

namespace digger
{
	class HighScoreScene final : public rift2d::Scene
	{
	public:
		HighScoreScene();
		~HighScoreScene() override = default;
		HighScoreScene(const HighScoreScene& other) = delete;
		HighScoreScene(HighScoreScene&& other) noexcept = delete;
		HighScoreScene& operator=(const HighScoreScene& other) = delete;
		HighScoreScene& operator=(HighScoreScene&& other) noexcept = delete;

	private:
		virtual void init() override;
	};


}
