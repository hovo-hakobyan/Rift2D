#pragma once
#include "Interfaces.h"

namespace digger
{
	class GoldActivateState final : public rift2d::IState
	{
	public:
		GoldActivateState() = default;
		~GoldActivateState() override = default;
		GoldActivateState(const GoldActivateState& other) = delete;
		GoldActivateState(GoldActivateState&& other) = delete;
		GoldActivateState& operator=(const GoldActivateState& other) = delete;
		GoldActivateState& operator=(GoldActivateState&& other) = delete;

		virtual void onEnter(rift2d::GameObject* ) override{}
		virtual void onExit(rift2d::GameObject* ) override{}
		virtual void update(rift2d::GameObject* gameObject) override;

	private:
		float m_maxFallTime{ 1.f };
		float m_currentFallTime{ 0.f };
	};


}
