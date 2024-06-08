#include "HighScoreScene.h"

#include "FPSComponent.h"
#include "InputManager.h"
#include "Components/Leaderboard.h"

namespace digger
{
	HighScoreScene::HighScoreScene(): Scene("HighScoreScene")
	{
	}

	void HighScoreScene::init()
	{
		const auto go = createGameObject();
		go->addComponent<Leaderboard>(5);

	}

}
