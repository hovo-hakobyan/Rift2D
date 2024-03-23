#pragma once
#include "BaseComponent.h"

namespace rift2d
{
	class TextComponent;
}

namespace rift2d
{
	class ScoreComponent;
	class ScoreDisplayComponent : public BaseComponent, public IComponentWatcher
	{
	public:
		ScoreDisplayComponent(GameObject* owner, ScoreComponent* pScoreComponent);
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
		TextComponent* m_pTextComponent;
		unsigned int m_observerID{};

		void updateScore(int currentScore) const;
	};


}
