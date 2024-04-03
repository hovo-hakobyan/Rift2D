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
		uint8_t prefabId = -1;
		RiftColor color = RiftColor::Brown;
		std::string prefabName;
	};


	class WorldBuilder final : public BaseComponent
	{
	public:
		WorldBuilder(GameObject* owner, const TileInfo& info,const std::string& mapName);
		~WorldBuilder()override;
		WorldBuilder(const WorldBuilder& other) = delete;
		WorldBuilder(WorldBuilder&& other) = delete;
		WorldBuilder& operator=(const WorldBuilder& other) = delete;
		WorldBuilder& operator=(WorldBuilder&& other) = delete;

		void setTileInfo(const TileInfo& info);
		void addTileData(const TileData& data);
		static void buildLevel(const std::string& lvlName);

		virtual void init() override;
		virtual void onImGui() override;

	private:

		TileInfo m_TileInfo{};
		std::vector<TileData> m_availableTileData{};
		std::vector<TileData> m_tiles{};

		TileData m_currentTileData{};
		bool m_isBrushSelected{};

		uint8_t m_nrRows{};
		uint8_t m_nrCols{};

		std::string m_mapName{};

		void saveLevelToFile(const std::string& name) const;
	};


}
