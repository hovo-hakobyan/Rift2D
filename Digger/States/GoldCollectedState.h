#pragma once
#include "Interfaces.h"

namespace digger
{
	class GoldCollectedState final :public rift2d::IState
	{
	public:
		GoldCollectedState() = default;
		~GoldCollectedState() override = default;
		GoldCollectedState(const GoldCollectedState& other) = delete;
		GoldCollectedState(GoldCollectedState&& other) = delete;
		GoldCollectedState& operator=(const GoldCollectedState& other) = delete;
		GoldCollectedState& operator=(GoldCollectedState&& other) = delete;

		void onEnter(rift2d::GameObject* gameObject) override;
		void update(rift2d::GameObject* gameObject) override;
		void onExit(rift2d::GameObject* gameObject) override;
	};


}
