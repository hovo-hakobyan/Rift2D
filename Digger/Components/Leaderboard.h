#pragma once
#include "BaseComponent.h"

namespace digger
{
	class Leaderboard final : public rift2d::BaseComponent
	{
	public:
		Leaderboard(rift2d::GameObject* owner, int num);
		virtual ~Leaderboard() override = default;
		Leaderboard(const Leaderboard& other) = delete;
		Leaderboard(Leaderboard&& other) = delete;
		Leaderboard& operator=(const Leaderboard& other) = delete;
		Leaderboard& operator=(Leaderboard&& other) = delete;

		virtual void init() override;
	private:
		int m_num{};
	};


}
