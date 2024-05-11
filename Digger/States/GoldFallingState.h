#pragma once
#include <glm/vec2.hpp>

#include "Interfaces.h"

namespace digger
{
	class GoldFallingState final : public rift2d::IState
	{
	public:
		GoldFallingState() = default;
		~GoldFallingState() override = default;
		GoldFallingState(const GoldFallingState& other) = delete;
		GoldFallingState(GoldFallingState&& other) = delete;
		GoldFallingState& operator=(const GoldFallingState& other) = delete;
		GoldFallingState& operator=(GoldFallingState&& other) = delete;

		void onEnter(rift2d::GameObject* gameObject) override;
		void update(rift2d::GameObject* gameObject) override;
		void onExit(rift2d::GameObject* gameObject) override;

	private:
		bool hitsGround(rift2d::GameObject* go);

		float m_fallDistance{ 0.f };
		int m_nrStoriesToExplode{ 2 };
		int m_startingTileIdx{};
		glm::vec2 m_startPosition{};
	};


}
