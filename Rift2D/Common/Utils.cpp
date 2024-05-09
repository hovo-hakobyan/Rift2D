#include "Utils.h"

#include "Settings.h"

namespace  rift2d
{
	//From Alex Kougentakos

	glm::vec2 Utils::pixelToMeters(const glm::vec2& pixelPos)
	{
		return { pixelPos.x * settings::MPP, pixelPos.y * settings::MPP };
	}

	glm::vec2 Utils::metersToPixels(const glm::vec2& meterPos)
	{
		return { meterPos.x * settings::PPM, meterPos.y * settings::PPM };
	}

	int Utils::indexFromPosition(int x, int y, int nrCols)
	{
		const int gridX = x / settings::TILE_WIDTH;
		const int gridY = y / settings::TILE_HEIGHT;

		return gridY * nrCols + gridX;
	}
}
