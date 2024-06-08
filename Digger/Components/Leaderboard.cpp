#include "Leaderboard.h"
#include "GameObject.h"
#include "ResourceManager.h"
#include "Scene.h"
#include "SceneManager.h"
#include "ScoreSave.h"
#include "Settings.h"
#include "TextComponent.h"


namespace digger
{
	Leaderboard::Leaderboard(rift2d::GameObject* owner, int num) :
		BaseComponent(owner), m_num(num)
	{
	}

	void Leaderboard::init()
	{
		BaseComponent::init();
		if(auto owner = getOwner())
		{
			auto saveData = std::make_unique<rift2d::ScoreSave>("diggerScore.rdata");
			auto leaderBoard = saveData->getTopScores(m_num);

			auto font = rift2d::ResourceManager::GetInstance().loadFont("Lingua.otf", 40);
			auto scene = rift2d::SceneManager::GetInstance().getActiveScene();
			glm::vec2 pos{ 10.f,10.f };
			float step = 60.f;
			for (const auto& data : leaderBoard)
			{
				auto go = scene->createGameObject();
				go->addComponent<rift2d::TextComponent>(std::format("{} - {}", data.name, data.score),font);
				go->getTransform()->setWorldPosition(pos);

				pos.y += step;
			}
			
		}
	}
}
