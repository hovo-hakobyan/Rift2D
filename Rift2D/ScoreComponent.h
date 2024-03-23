#pragma once
#include "BaseComponent.h"
#include "Subject.h"

namespace rift2d
{
	class ScoreComponent : public rift2d::BaseComponent
	{
	public:
		ScoreComponent(GameObject* owner);
		virtual ~ScoreComponent() override = default;
		ScoreComponent(const ScoreComponent& other) = delete;
		ScoreComponent(ScoreComponent&& other) = delete;
		ScoreComponent& operator=(const ScoreComponent& other) = delete;
		ScoreComponent& operator=(ScoreComponent&& other) = delete;

		virtual void init() override;
		virtual void end() override;

		void modify(int amount);
		Subject<int>* onScoreChangeEvent() const { return m_pOnScoreChange.get(); }

	private:
		int m_currentScore{};
		std::unique_ptr<Subject<int>> m_pOnScoreChange;
	};
}
