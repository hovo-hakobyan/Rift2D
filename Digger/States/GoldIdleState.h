#pragma once
#include "Interfaces.h"

namespace digger
{
	
	class GoldIdleState final : public rift2d::IState
	{
	public:
		GoldIdleState() = default;
		~GoldIdleState() override = default;
		GoldIdleState(const GoldIdleState& other) = delete;
		GoldIdleState(GoldIdleState&& other) = delete;
		GoldIdleState& operator=(const GoldIdleState& other) = delete;
		GoldIdleState& operator=(GoldIdleState&& other) = delete;

		void onEnter(rift2d::GameObject* gameObject) override;
		void update(rift2d::GameObject* gameObject) override;
		void onExit(rift2d::GameObject* gameObject) override;

	private:
		bool shouldFall(rift2d::GameObject* gameObj);
	
	};


}
