#include "WorldBuilder.h"
#include <algorithm>
#include <imgui.h>
#include <fstream>
#include "Renderer.h"
#include <filesystem>

#include "Exception.h"

rift2d::WorldBuilder::WorldBuilder(GameObject* owner, const TileInfo& info,const std::string& mapName):
BaseComponent(owner),m_TileInfo(info),m_mapName(mapName)
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
		return data.prefabId == d.prefabId;
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
			m_currentTileData.prefabId = tileData.prefabId;
		}
		ImGui::SameLine();
	}
	ImGui::PushStyleColor(ImGuiCol_Button, ImVec4{0.5f,0.5f,0.5f,1.f});
	if (ImGui::Button("Save Level"))
	{
		try
		{
			saveLevelToFile(m_mapName); 
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
		ImGui::Text("Level saved successfully!");
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
					tile.prefabId = m_currentTileData.prefabId;
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

void rift2d::WorldBuilder::saveLevelToFile(const std::string& name) const
{
	const std::filesystem::path directoryPath = "Levels";
	bool dirCreated = std::filesystem::create_directories(directoryPath);
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

	//write rows and cols
	outFile.write(reinterpret_cast<const char*>(&m_nrRows), sizeof(m_nrRows));
	outFile.write(reinterpret_cast<const char*>(&m_nrCols), sizeof(m_nrCols));

	//write tile data
	for (const auto& tile : m_tiles)
	{
		outFile.write(reinterpret_cast<const char*>(&tile.prefabId), sizeof(tile.prefabId));
	}
	if(!outFile)
	{
		THROW_RIFT_EXCEPTION("Cannot save " + name + ".riftmap, writing failed", RiftExceptionType::Error);
	}

	outFile.close();
	
}

void rift2d::WorldBuilder::buildLevel(const std::string& lvlName)
{
	std::ifstream inFile("Levels/" + lvlName + ".riftmap", std::ios::binary);
	if(!inFile)
	{
		THROW_RIFT_EXCEPTION("Cannot open " + lvlName + ".riftmap. It doesn't exist", RiftExceptionType::Error);
	}

	uint8_t rows, cols;
	inFile.read(reinterpret_cast<char*>(&rows), sizeof(rows));
	inFile.read(reinterpret_cast<char*>(&cols), sizeof(cols));

	std::vector<TileData> tiles;
	tiles.resize(rows * cols);
	for (auto& tile : tiles)
	{
		inFile.read(reinterpret_cast<char*>(&tile.prefabId), sizeof(tile.prefabId));
	}

	if(!inFile)
	{
		THROW_RIFT_EXCEPTION("Cannot read data inside " + lvlName + ".riftmap.", RiftExceptionType::Error);
	}

	inFile.close();
	
}