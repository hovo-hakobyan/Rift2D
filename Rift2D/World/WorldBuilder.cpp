#include "WorldBuilder.h"
#include <algorithm>
#include <imgui.h>
#include <fstream>
#include "Renderer.h"
#include <filesystem>
#include <regex>
#include "Scene.h"
#include "Exception.h"
#include "SceneManager.h"

int rift2d::WorldBuilder::m_saveMapHighestIdx = -1;

rift2d::WorldBuilder::WorldBuilder(GameObject* owner, const TileInfo& info, uint8_t nrLayers):
BaseComponent(owner),m_TileInfo(info),m_nrLayers(nrLayers)
{

}

rift2d::WorldBuilder::~WorldBuilder() = default;


void rift2d::WorldBuilder::setTileInfo(const TileInfo& info)
{
	m_TileInfo = info;
}

void rift2d::WorldBuilder::addLayerInfo(const LayerInfo& info)
{
	//If the current layer info does not exist (to avoid duplicates)
	if (std::ranges::none_of(m_layerInfo, [info](const LayerInfo& d)
		{
			return info.prefabRegistryId == d.prefabRegistryId;
		}))
	{
		m_layerInfo.push_back(info);
	}
}

void rift2d::WorldBuilder::setWorldPadding(float left, float top)
{
	m_worldPadding.x = left;
	m_worldPadding.y = top;
}


void rift2d::WorldBuilder::init()
{
	BaseComponent::init();
	if (m_nrLayers <= 0) THROW_RIFT_EXCEPTION("Number of layers in worldbuilder must be greater than 0", RiftExceptionType::Error);

	const auto windowSize = Renderer::GetInstance().getWindowSize();
	m_nrCols =static_cast<uint16_t>( static_cast<uint16_t>(windowSize.x) / m_TileInfo.width);
	m_nrRows = static_cast<uint16_t>(static_cast<uint16_t>(windowSize.y) / m_TileInfo.height);

	m_tileLayerData.resize(m_nrLayers);
	for (auto& element : m_tileLayerData)
	{
		element.layerInfoVec.resize(static_cast<size_t>(m_nrCols * m_nrRows));
	}

	//first layer should be available for editing
	m_layerEditStates.resize(m_nrLayers, 0);
	m_layerEditStates[0] = 1;
}

void rift2d::WorldBuilder::onImGui()
{
	// Set the initial position of the window to the top-left corner
	ImGui::SetNextWindowPos(ImVec2(0, 0));
	const auto windowSize = Renderer::GetInstance().getWindowSize();
	ImGui::SetNextWindowSize(ImVec2(windowSize.x, windowSize.y));

	// Window flags
	ImGuiWindowFlags window_flags = 0;
	window_flags |= ImGuiWindowFlags_NoTitleBar;          
	window_flags |= ImGuiWindowFlags_NoResize;            
	window_flags |= ImGuiWindowFlags_NoMove;              
	window_flags |= ImGuiWindowFlags_NoScrollbar;         
	window_flags |= ImGuiWindowFlags_NoScrollWithMouse;   
	window_flags |= ImGuiWindowFlags_NoCollapse;          
	window_flags |= ImGuiWindowFlags_NoBackground;

	//Show the available tile options that can be selected
	ImGui::Begin("World Builder",nullptr,window_flags);
	for(const auto& info : m_layerInfo)
	{
		if(ImGui::Button(info.prefabName.c_str()))
		{
			m_currentLayerInfo.color = info.color;
			m_currentLayerInfo.prefabRegistryId = info.prefabRegistryId;
			m_isBrushSelected = true;
		}
		ImGui::SameLine();
	}
	ImGui::PushStyleColor(ImGuiCol_Button, ImVec4{0.5f,0.5f,0.5f,1.f});
	if (ImGui::Button("Save Level"))
	{
		try
		{
			saveLevelToFile(); 
		}
		catch (const RiftException& e)
		{
			e.logToFile();
			throw;
		}
		
		// Show a notification popup
		ImGui::OpenPopup("Save Notification");
		
	}
	ImGui::PopStyleColor();

	//if level is saved show feedback
	if (ImGui::BeginPopup("Save Notification"))
	{
		ImGui::Text(std::format("Level {} saved successfully!",m_saveMapHighestIdx).c_str());
		if (ImGui::Button("OK"))
		{
			ImGui::CloseCurrentPopup();
		}
		ImGui::EndPopup();
	}

	//Slider for layers
	ImGui::PushItemWidth(100);
	ImGui::SliderInt("Layer", &m_currentLayerNr, 0, m_nrLayers - 1, "Layer %d");
	ImGui::PopItemWidth();

	ImGui::NewLine();
	//Visualize selected tile type using it's color
	if (m_isBrushSelected)
	{
		ImVec2 mousePos = ImGui::GetMousePos();
		ImDrawList* drawList = ImGui::GetForegroundDrawList();

		ImVec4 imColor = ImVec4(static_cast<float>(m_currentLayerInfo.color.r) / 255.0f, static_cast<float>(m_currentLayerInfo.color.g) / 255.0f, 
			static_cast<float>(m_currentLayerInfo.color.b) / 255.0f,static_cast<float>( m_currentLayerInfo.color.a) / 255.0f);
		drawList->AddCircleFilled(mousePos, 10.f, ImColor(imColor), 12);
	}

	ImVec2 originalSpacing = ImGui::GetStyle().ItemSpacing;
	ImGui::GetStyle().ItemSpacing = ImVec2(0, 0);

	auto& layer = m_tileLayerData[m_currentLayerNr];
	//Draw the grid
	for(int row = 0; row < m_nrRows; ++row)
	{
		for(int col = 0; col < m_nrCols; ++col)
		{
			int id = row * m_nrCols + col;
			ImGui::PushID(id);

			auto& tile = layer.layerInfoVec[id];
			ImVec4 tileColor = ImVec4(static_cast<float>(tile.color.r )/ 255.f, static_cast<float>(tile.color.g) / 255.f, static_cast<float>(tile.color.b) / 255.f, static_cast<float>(tile.color.a) / 255.f);

			//temporary color change
			ImGui::PushStyleColor(ImGuiCol_Button, tileColor);

			if (ImGui::Button("###tile", ImVec2(m_TileInfo.width, m_TileInfo.height)))
			{
				if(m_isBrushSelected)
				{
					tile.color = m_currentLayerInfo.color;
					tile.prefabRegistryId = m_currentLayerInfo.prefabRegistryId;
				}
			}

			ImGui::PopStyleColor();
			ImGui::PopID();

			if (col < m_nrCols - 1) ImGui::SameLine();
		}
	}

	

	ImGui::GetStyle().ItemSpacing = originalSpacing;
	ImGui::End();
}

void rift2d::WorldBuilder::saveLevelToFile()
{
	const std::filesystem::path directoryPath = "../Levels";
	const std::string name = getNextLevelName();
	const bool dirCreated = std::filesystem::create_directories(directoryPath);
	if (!dirCreated && !std::filesystem::exists(directoryPath))
	{
		THROW_RIFT_EXCEPTION("Cannot save level " + name + " because Directory doesn't exist", RiftExceptionType::Error);
	}

	const std::filesystem::path fullPath = directoryPath / name;
	std::ofstream outFile(fullPath.string() + ".riftmap", std::ios::binary);

	if(!outFile)
	{
		THROW_RIFT_EXCEPTION("Cannot open " + name + ".riftmap to save the level", RiftExceptionType::Error);
	}

	//Write number of tiles to .riftmap
	const uint16_t nrTiles{ static_cast<uint16_t>(m_nrCols * m_nrRows) };
	outFile.write(reinterpret_cast<const char*>(&nrTiles), sizeof(nrTiles));

	//write number of layers to .riftmap
	outFile.write(reinterpret_cast<const char*>(&m_nrLayers), sizeof(m_nrLayers));

	glm::vec2 tilePos{ m_worldPadding};

	for (int row = 0; row <m_nrRows; ++row)
	{
		for (int col = 0; col < m_nrCols; ++col)
		{
			const int tileIdx{ row * m_nrCols + col };
			writeTileData(outFile, tileIdx, tilePos);

			if (!outFile)
			{
				THROW_RIFT_EXCEPTION("Cannot save " + name + ".riftmap, writing failed", RiftExceptionType::Error);
			}

			tilePos.x += static_cast<float>(m_TileInfo.width);

		}
		tilePos.y += static_cast<float>(m_TileInfo.height);
		tilePos.x = 0.f;
	}

	outFile.close();
	
}

std::vector<rift2d::TileSaveData> rift2d::WorldBuilder::readSaveData(const std::string& lvlName)
{

	std::ifstream inFile("../Levels/" + lvlName + ".riftmap", std::ios::binary);
	if (!inFile)
	{
		THROW_RIFT_EXCEPTION("Cannot open " + lvlName + ".riftmap. It doesn't exist", RiftExceptionType::Error);
	}

	//read number of tiles
	uint16_t nrTiles{};
	inFile.read(reinterpret_cast<char*>(&nrTiles), sizeof(nrTiles));

	uint8_t nrLayers{};
	//read number of layers
	inFile.read(reinterpret_cast<char*>(&nrLayers), sizeof(nrLayers));

	std::vector<TileSaveData> tileSaveData;
	tileSaveData.resize(nrTiles);

	for (auto& saveData : tileSaveData)
	{
		saveData.prefabRegistryIds.resize(nrLayers);
		for(int layerIdx = 0; layerIdx < static_cast<int>(nrLayers); ++layerIdx)
		{
			inFile.read(reinterpret_cast<char*>(&saveData.prefabRegistryIds[layerIdx]), sizeof(saveData.prefabRegistryIds[layerIdx]));
		}

		inFile.read(reinterpret_cast<char*>(&saveData.spawnLocation), sizeof(saveData.spawnLocation));
	}

	if (!inFile)
	{
		THROW_RIFT_EXCEPTION("Cannot read data inside " + lvlName + ".riftmap.", RiftExceptionType::Error);
	}

	inFile.close();
	return tileSaveData;

}

void rift2d::WorldBuilder::writeTileData(std::ofstream& outFile,int tileIdx, const glm::vec2& tilePos)
{
	for (const auto& layer : m_tileLayerData)
	{
		auto& tile = layer.layerInfoVec[tileIdx];
		outFile.write(reinterpret_cast<const char*>(&tile.prefabRegistryId), sizeof(tile.prefabRegistryId));
	}
	// Write the tile position once per tile, after all its layers have been written
	outFile.write(reinterpret_cast<const char*>(&tilePos), sizeof(tilePos));
}

std::string rift2d::WorldBuilder::getNextLevelName() const
{
	if (m_saveMapHighestIdx != -1) return "level" + std::to_string(++m_saveMapHighestIdx);

	int maxLevelNum = -1;
	const std::regex levelRegex("level(\\d+)\\.riftmap");

	for (const auto& entry : std::filesystem::directory_iterator("../Levels"))
	{
		std::smatch matches;
		std::string filename = entry.path().filename().string();
		if (std::regex_match(filename, matches, levelRegex) && matches.size() == 2)
		{
			int levelNum = std::stoi(matches[1].str());
			maxLevelNum = std::max(maxLevelNum, levelNum);
		}
	}

	m_saveMapHighestIdx = maxLevelNum +1;
	// Create the next level name by incrementing the highest found level number
	return "level" + std::to_string(m_saveMapHighestIdx);
}



void rift2d::WorldBuilder::buildLevel(const std::string& lvlName)
{
	const auto tileSaveDatas = readSaveData(lvlName);
	if (tileSaveDatas.empty()) return;

	const auto pScene = SceneManager::GetInstance().getActiveScene();
	auto& prefabRegistry = WorldBuilderPrefabRegistry::GetInstance();

	for (const auto & info : tileSaveDatas)
	{
		for (const auto data : info.prefabRegistryIds)
		{
			prefabRegistry.createPrefab(glm::vec3{ info.spawnLocation.x,info.spawnLocation.y,1.f }, data, pScene);
		}
		
	}

	
}
