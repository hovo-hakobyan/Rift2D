#pragma once
#include "Interfaces.h"

namespace digger
{
	enum class PlayMode
	{
		Singleplayer, CoOp, Versus
	};
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
		void setPlayMode(PlayMode playMode) { m_playMode = playMode; }
		PlayMode getPlayMode() const { return m_playMode; }

		std::string getCurrentPlyerName() const { return m_name; }
		int getScore() const { return m_score; }
	private:
		PlayMode m_playMode{ PlayMode::Singleplayer };
		int m_score{};
		std::string m_name{};
	};
}
