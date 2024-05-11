#pragma once
#include "Interfaces.h"

namespace digger
{

	class GoldExplodingState final : public rift2d::IState
	{
	public:

		GoldExplodingState() = default;
		~GoldExplodingState() override = default;
		GoldExplodingState(const GoldExplodingState& other) = delete;
		GoldExplodingState(GoldExplodingState&& other) = delete;
		GoldExplodingState& operator=(const GoldExplodingState& other) = delete;
		GoldExplodingState& operator=(GoldExplodingState&& other) = delete;

		void onEnter(rift2d::GameObject* gameObject) override;
		void update(rift2d::GameObject* gameObject) override;
		void onExit(rift2d::GameObject* gameObject) override;
	};


}
