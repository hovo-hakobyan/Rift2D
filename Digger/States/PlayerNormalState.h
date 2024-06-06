#pragma once

#include "Interfaces.h"

namespace digger
{
	class HealthComponent;
	class PlayerNormalState final : public rift2d::IState
	{
	public:

		PlayerNormalState(HealthComponent* pHealth);
		~PlayerNormalState() override = default;
		PlayerNormalState(const PlayerNormalState& other) = delete;
		PlayerNormalState(PlayerNormalState&& other) = delete;
		PlayerNormalState& operator=(const PlayerNormalState& other) = delete;
		PlayerNormalState& operator=(PlayerNormalState&& other) = delete;

		void onEnter(rift2d::GameObject* gameObject) override;
		void update(rift2d::GameObject* gameObject) override;
		void onExit(rift2d::GameObject* gameObject) override;

	private:
		HealthComponent* m_pHealth{};
		bool m_isDead{ false };
		unsigned int m_observerId{};

		void onPlayerHealthChanged(int newHealth);
	};
}
