#include "WorldBuilder.h"
#include <algorithm>
#include <imgui.h>
#include <iostream>

#include "Renderer.h"

rift2d::WorldBuilder::WorldBuilder(GameObject* owner, const TileInfo& info):
BaseComponent(owner),m_TileInfo(info)
{

}

rift2d::WorldBuilder::~WorldBuilder() = default;


void rift2d::WorldBuilder::addTileData(const TileData& data)
{
	//If the current tile data does not exist
	if(std::ranges::none_of(m_tileData,[data](const TileData& d)
	{
		return data.name == d.name;
	}))
	{
		m_tileData.push_back(data);
	}
}

void rift2d::WorldBuilder::init()
{
	BaseComponent::init();

	const auto windowSize = Renderer::GetInstance().getWindowSize();
	m_nrCols =static_cast<int>( windowSize.x / m_TileInfo.width);
	m_nrRows = static_cast<int>(windowSize.y / m_TileInfo.height);

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
	for(const auto& tileData : m_tileData)
	{
		if(ImGui::Button(tileData.name.c_str()))
		{
			m_currentBrushColor = tileData.color;
			m_isBrushSelected = true;
		}
		ImGui::SameLine();
	}

	ImGui::NewLine();
	//Visualize selected tile type using it's color
	if (m_isBrushSelected)
	{
		ImVec2 mousePos = ImGui::GetMousePos();
		ImDrawList* drawList = ImGui::GetForegroundDrawList();

		ImVec4 imColor = ImVec4(m_currentBrushColor.r / 255.0f, m_currentBrushColor.g / 255.0f, m_currentBrushColor.b / 255.0f, m_currentBrushColor.a / 255.0f);
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
					tile.color = m_currentBrushColor;
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
