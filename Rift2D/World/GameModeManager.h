#pragma once
#include <concepts>
#include <memory>

#include "Singleton.h"

namespace rift2d
{
	class IGameMode;
}

namespace rift2d
{
	class GameModeManager final : public Singleton<GameModeManager>
	{
	public:
		~GameModeManager() override;
		GameModeManager(const GameModeManager& other) = delete;
		GameModeManager(GameModeManager&& other) noexcept = delete;
		GameModeManager& operator=(const GameModeManager& other) = delete;
		GameModeManager& operator=(GameModeManager&& other) noexcept = delete;

		template<typename GameMode>
		requires std::derived_from<GameMode,IGameMode>
		IGameMode* createGameMode()
		{
			m_pGameMode = std::make_unique<GameMode>();
			return m_pGameMode.get();
		}

		IGameMode* getGameMode() const { return m_pGameMode.get(); }

	private:
		friend class Singleton;
		GameModeManager() = default;

		std::unique_ptr<IGameMode> m_pGameMode;

	};

}
