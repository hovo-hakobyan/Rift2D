#pragma once
#include <cstdint>
#include <functional>
#include <string>
#include <vector>
#include "BaseComponent.h"
#include "Color.h"
#include "Scene.h"
#include "Singleton.h"

namespace rift2d
{
	class WorldBuilderPrefabRegistry : public Singleton<WorldBuilderPrefabRegistry>
	{
	public:
		~WorldBuilderPrefabRegistry() override = default;

		void registerPrefabCreator(uint8_t prefabId,const std::function<GameObject* (const glm::vec3& ,Scene*)>& creator)
		{
			m_prefabCreators[prefabId] = creator;
		}

		GameObject* createPrefab(const glm::vec3& loc, uint8_t prefabId, Scene* scene)
		{
			if (m_prefabCreators.contains(prefabId))
			{
				return m_prefabCreators[prefabId](loc, scene);
			}
			return nullptr;
		}


	private:
		friend Singleton;
		WorldBuilderPrefabRegistry() = default;

		std::unordered_map<uint8_t, std::function<GameObject*(const glm::vec3&,Scene*)>> m_prefabCreators;

	};

	struct TileInfo
	{
		uint16_t width;
		uint16_t height;
	};

	struct TileData
	{
		uint8_t prefabRegistryId = 0;
		RiftColor color = RiftColor::Brown;
		std::string prefabName;
	};

	struct WorldInfo
	{
		uint8_t prefabRegistryId;
		glm::vec2 spawnLocation;
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

		uint16_t m_nrRows{};
		uint16_t m_nrCols{};

		std::string m_mapName{};
		static int m_saveMapHighestIdx;

		void saveLevelToFile() const;
		std::string getNextLevelName() const;

		static std::vector<WorldInfo> readWorldData(const std::string& lvlName);
	};


}
