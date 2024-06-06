#pragma once
#include "Interfaces.h"

namespace digger
{
	class PlayerDeadState final : public rift2d::IState
	{
	public:

		PlayerDeadState() = default;
		~PlayerDeadState() override = default;
		PlayerDeadState(const PlayerDeadState& other) = delete;
		PlayerDeadState(PlayerDeadState&& other) = delete;
		PlayerDeadState& operator=(const PlayerDeadState& other) = delete;
		PlayerDeadState& operator=(PlayerDeadState&& other) = delete;

		void onEnter(rift2d::GameObject* gameObject) override;
		void update(rift2d::GameObject* gameObject) override;
		void onExit(rift2d::GameObject*) override;

	private:
		float m_maxDeadTime{ 3.f };
		float m_currentDeadTime{ 0.f };
	};

}

