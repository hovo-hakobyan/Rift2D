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
}
