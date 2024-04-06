#include "WorldBuilder.h"
#include <algorithm>
#include <imgui.h>
#include <fstream>
#include "Renderer.h"
#include <filesystem>
#include <regex>

#include "Exception.h"
#include "SceneManager.h"

int rift2d::WorldBuilder::m_saveMapHighestIdx = -1;

rift2d::WorldBuilder::WorldBuilder(GameObject* owner, const TileInfo& info):
BaseComponent(owner),m_TileInfo(info)
{

}

rift2d::WorldBuilder::~WorldBuilder() = default;


void rift2d::WorldBuilder::setTileInfo(const TileInfo& info)
{
	m_TileInfo = info;
}

void rift2d::WorldBuilder::addTileData(const TileData& data)
{
	//If the current tile data does not exist
	if(std::ranges::none_of(m_availableTileData,[data](const TileData& d)
	{
		return data.prefabRegistryId == d.prefabRegistryId;
	}))
	{
		m_availableTileData.push_back(data);
	}
}



void rift2d::WorldBuilder::init()
{
	BaseComponent::init();

	const auto windowSize = Renderer::GetInstance().getWindowSize();
	m_nrCols =static_cast<uint8_t>( windowSize.x / m_TileInfo.width);
	m_nrRows = static_cast<uint8_t>(windowSize.y / m_TileInfo.height);

	m_tiles.resize(m_nrCols * m_nrRows);
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
	for(const auto& tileData : m_availableTileData)
	{
		if(ImGui::Button(tileData.prefabName.c_str()))
		{
			m_currentTileData.color = tileData.color;
			m_isBrushSelected = true;
			m_currentTileData.prefabRegistryId = tileData.prefabRegistryId;
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
	

	ImGui::NewLine();
	//Visualize selected tile type using it's color
	if (m_isBrushSelected)
	{
		ImVec2 mousePos = ImGui::GetMousePos();
		ImDrawList* drawList = ImGui::GetForegroundDrawList();

		ImVec4 imColor = ImVec4(m_currentTileData.color.r / 255.0f, m_currentTileData.color.g / 255.0f, m_currentTileData.color.b / 255.0f, m_currentTileData.color.a / 255.0f);
		drawList->AddCircleFilled(mousePos, 10.f, ImColor(imColor), 12);
	}

	ImVec2 originalSpacing = ImGui::GetStyle().ItemSpacing;
	ImGui::GetStyle().ItemSpacing = ImVec2(0, 0);
	//Draw the grid
	for(int row = 0; row < m_nrRows; ++row)
	{
		for(int col = 0; col < m_nrCols; ++col)
		{
			int id = row * m_nrCols + col;
			ImGui::PushID(id);

			auto& tile = m_tiles[id];
			ImVec4 tileColor = ImVec4(tile.color.r / 255.f, tile.color.g / 255.f, tile.color.b / 255.f, tile.color.a / 255.f);

			//temporary color change
			ImGui::PushStyleColor(ImGuiCol_Button, tileColor);

			if (ImGui::Button("###tile", ImVec2(m_TileInfo.width, m_TileInfo.height)))
			{
				if(m_isBrushSelected)
				{
					tile.color = m_currentTileData.color;
					tile.prefabRegistryId = m_currentTileData.prefabRegistryId;
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

void rift2d::WorldBuilder::saveLevelToFile() const
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

	glm::vec2 tilePos{ 0.f,0.f};
	for (int row = 0; row <m_nrRows; ++row)
	{
		for (int col = 0; col < m_nrCols; ++col)
		{
			const int tileIdx{ row * m_nrCols + col };
			if (tileIdx >= static_cast<int>(m_tiles.size()))
				THROW_RIFT_EXCEPTION("Tile data inside .riftmap is corrupt. Less tiles than rows * cols", RiftExceptionType::Error);

			auto& tile = m_tiles[tileIdx];

			//Write current tile prefab id
			outFile.write(reinterpret_cast<const char*>(&tile.prefabRegistryId), sizeof(tile.prefabRegistryId));

			//write current tile position
			outFile.write(reinterpret_cast<const char*>(&tilePos),sizeof(tilePos));

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

std::vector<rift2d::WorldInfo> rift2d::WorldBuilder::readWorldData(const std::string& lvlName)
{

	std::ifstream inFile("../Levels/" + lvlName + ".riftmap", std::ios::binary);
	if (!inFile)
	{
		THROW_RIFT_EXCEPTION("Cannot open " + lvlName + ".riftmap. It doesn't exist", RiftExceptionType::Error);
	}

	//read number of tiles
	uint16_t nrTiles{};
	inFile.read(reinterpret_cast<char*>(&nrTiles), sizeof(nrTiles));

	std::vector<WorldInfo> worldInfo;
	worldInfo.resize(nrTiles);

	for (auto& info : worldInfo)
	{
		inFile.read(reinterpret_cast<char*>(&info.prefabRegistryId), sizeof(info.prefabRegistryId));
		inFile.read(reinterpret_cast<char*>(&info.spawnLocation), sizeof(info.spawnLocation));
	}

	if (!inFile)
	{
		THROW_RIFT_EXCEPTION("Cannot read data inside " + lvlName + ".riftmap.", RiftExceptionType::Error);
	}

	inFile.close();
	return worldInfo;

}

void rift2d::WorldBuilder::buildLevel(const std::string& lvlName)
{
	const auto worldInfo = readWorldData(lvlName);
	if (worldInfo.empty()) return;

	const auto pScene = SceneManager::GetInstance().getActiveScene();
	auto& prefabRegistry = WorldBuilderPrefabRegistry::GetInstance();

	for (const auto & info : worldInfo)
	{
		prefabRegistry.createPrefab(glm::vec3{ info.spawnLocation.x,info.spawnLocation.y,1.f }, info.prefabRegistryId, pScene);
	}

	
}
