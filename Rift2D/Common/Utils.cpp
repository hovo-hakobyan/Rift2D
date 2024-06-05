#include "Utils.h"
#include "Settings.h"

namespace  rift2d
{
	//From Alex Kougentakos
	glm::vec2 Utils::pixelToMeters(const glm::vec2& pixelPos)
	{
		return { pixelPos.x * riftSettings::MPP, pixelPos.y * riftSettings::MPP };
	}

	glm::vec2 Utils::metersToPixels(const glm::vec2& meterPos)
	{
		return { meterPos.x * riftSettings::PPM, meterPos.y * riftSettings::PPM };
	}

	int Utils::indexFromPosition(int x, int y, int nrCols)
	{
		const int gridX = x / riftSettings::TILE_WIDTH;
		const int gridY = y / riftSettings::TILE_HEIGHT;

		return gridY * nrCols + gridX;
	}

	int Utils::indexFromRowsCols(int row, int col, int nrCols)
	{
		return row * nrCols + col;
	}

	std::tuple<int, int> Utils::getRowColIdx(const glm::vec2& pos)
	{
		int colIdx = static_cast<int>(pos.x) / riftSettings::TILE_WIDTH;
		int rowIdx = static_cast<int>(pos.y) / riftSettings::TILE_HEIGHT;

		return std::make_tuple(rowIdx, colIdx);
	}

	glm::vec2 Utils::positionFromRowCol(int row, int col)
	{
		const float x =static_cast<float>( col * riftSettings::TILE_WIDTH) + riftSettings::TILE_WIDTH / 2.f;
		const float y =static_cast<float>( row * riftSettings::TILE_HEIGHT) + riftSettings::TILE_HEIGHT / 2.f;
		return {x, y};
	}
}
