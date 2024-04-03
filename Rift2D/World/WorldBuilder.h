#pragma once
#include <cstdint>
#include <string>
#include <vector>
#include "BaseComponent.h"
#include "Color.h"


namespace rift2d
{
	struct TileInfo
	{
		uint16_t width;
		uint16_t height;
	};

	struct TileData
	{
		std::string name;
		RiftColor color = RiftColor::Black;
	};

	class WorldBuilder final : public BaseComponent
	{
	public:
		WorldBuilder(GameObject* owner, const TileInfo& info);
		~WorldBuilder()override;
		WorldBuilder(const WorldBuilder& other) = delete;
		WorldBuilder(WorldBuilder&& other) = delete;
		WorldBuilder& operator=(const WorldBuilder& other) = delete;
		WorldBuilder& operator=(WorldBuilder&& other) = delete;

		void addTileData(const TileData& data);

		virtual void init() override;
		virtual void onImGui() override;
	private:
		struct Tile
		{
			uint8_t index = 0;
			RiftColor color = RiftColor::Brown;
		};

		TileInfo m_TileInfo{};
		std::vector<TileData> m_tileData{};
		std::vector<Tile> m_tiles{};

		RiftColor m_currentBrushColor{};
		bool m_isBrushSelected{};

		int m_nrRows{};
		int m_nrCols{};
	};


}
