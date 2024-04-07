#pragma once
#include <cstdint>
#include <functional>
#include <string>
#include <vector>
#include "Color.h"
#include <glm/vec2.hpp>
#include <glm/vec3.hpp>
#include "BaseComponent.h"
#include "Singleton.h"

namespace rift2d
{
	class Scene;
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

	struct LayerInfo
	{
		uint8_t prefabRegistryId = 0;
		RiftColor color = RiftColor::Gray;
		std::string prefabName;
	};

	struct TileLayerData
	{
		std::vector<LayerInfo> layerInfoVec;
	};

	struct TileSaveData
	{
		std::vector<uint8_t>prefabRegistryIds;
		glm::vec2 spawnLocation;
	};

	class WorldBuilder final : public BaseComponent
	{
	public:
		WorldBuilder(GameObject* owner, const TileInfo& info, uint8_t nrLayers);
		~WorldBuilder()override;
		WorldBuilder(const WorldBuilder& other) = delete;
		WorldBuilder(WorldBuilder&& other) = delete;
		WorldBuilder& operator=(const WorldBuilder& other) = delete;
		WorldBuilder& operator=(WorldBuilder&& other) = delete;

		void setTileInfo(const TileInfo& info);
		void addLayerInfo(const LayerInfo& info);
		static void buildLevel(const std::string& lvlName);

		virtual void init() override;
		virtual void onImGui() override;

	private:

		TileInfo m_TileInfo{};
		std::vector<LayerInfo> m_layerInfo{};
		std::vector<TileLayerData> m_tileLayerData{};

		LayerInfo m_currentLayerInfo{};
		bool m_isBrushSelected{};

		uint16_t m_nrRows{};
		uint16_t m_nrCols{};
		uint8_t m_nrLayers{};
		int m_currentLayerNr{0};
		std::vector<char> m_layerEditStates{}; //(special bool vector optimization, hence vector of char as an alternative) https://stackoverflow.com/questions/46115669/why-does-stdvectorbool-have-no-data
		static int m_saveMapHighestIdx;

		void saveLevelToFile();
		void writeTileData(std::ofstream& outFile, int tileIdx, const glm::vec2& tilePos);
		std::string getNextLevelName() const;
		static std::vector<TileSaveData> readSaveData(const std::string& lvlName);
	};


}
