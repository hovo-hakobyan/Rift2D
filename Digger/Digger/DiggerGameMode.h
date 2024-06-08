#pragma once
#include "Interfaces.h"

namespace digger
{
	class DiggerGameMode final : public rift2d::IGameMode
	{
	public:
		DiggerGameMode() = default;
		~DiggerGameMode() override = default;
		DiggerGameMode(const DiggerGameMode& other) = delete;
		DiggerGameMode(DiggerGameMode&& other) = delete;
		DiggerGameMode& operator=(const DiggerGameMode& other) = delete;
		DiggerGameMode& operator=(DiggerGameMode&& other) = delete;

		void addScore(int amount) { m_score+= amount; }
		void setCurrentPlayerName(const std::string& name) { m_name = name; }

		std::string getCurrentPlyerName() const { return m_name; }
		int getScore() const { return m_score; }
	private:

		int m_score{};
		std::string m_name{};
	};
}
