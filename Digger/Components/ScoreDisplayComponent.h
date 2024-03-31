#pragma once
#include "BaseComponent.h"


namespace rift2d
{
	class TextComponent;
}

namespace digger
{
	class ScoreComponent;
	class ScoreDisplayComponent : public rift2d::BaseComponent, public rift2d::IComponentWatcher
	{
	public:
		ScoreDisplayComponent(rift2d::GameObject* owner, ScoreComponent* pScoreComponent);
		virtual ~ScoreDisplayComponent() override = default;
		ScoreDisplayComponent(const ScoreDisplayComponent& other) = delete;
		ScoreDisplayComponent(ScoreDisplayComponent&& other) = delete;
		ScoreDisplayComponent& operator=(const ScoreDisplayComponent& other) = delete;
		ScoreDisplayComponent& operator=(ScoreDisplayComponent&& other) = delete;

		void onComponentRemoved(BaseComponent* component) override;

		virtual void init() override;
		virtual void end() override;

	private:
		ScoreComponent* m_pScoreComponent;
		rift2d::TextComponent* m_pTextComponent;
		unsigned int m_observerID{};

		void updateScore(int currentScore) const;
	};


}
