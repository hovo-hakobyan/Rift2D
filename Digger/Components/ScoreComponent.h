#pragma once
#include "BaseComponent.h"
#include "Subject.h"

namespace digger
{
	class ScoreComponent : public rift2d::BaseComponent
	{
	public:
		ScoreComponent(rift2d::GameObject* owner);
		virtual ~ScoreComponent() override = default;
		ScoreComponent(const ScoreComponent& other) = delete;
		ScoreComponent(ScoreComponent&& other) = delete;
		ScoreComponent& operator=(const ScoreComponent& other) = delete;
		ScoreComponent& operator=(ScoreComponent&& other) = delete;

		virtual void init() override;
		virtual void end() override;

		void modify(int amount);
		rift2d::Subject<int>* scoreChangeEvent() const { return m_pOnScoreChange.get(); }

	private:
		int m_currentScore{};

		std::unique_ptr<rift2d::Subject<int>> m_pOnScoreChange;
	};
}
