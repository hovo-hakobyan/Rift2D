#include "Utils.h"

#include "Settings.h"

namespace  rift2d
{
	//From Alex Kougentakos

	glm::vec2 Utils::pixelToMeters(glm::vec2 pixelPos)
	{
		return { pixelPos.x * settings::MPP, pixelPos.y * settings::MPP };
	}

	glm::vec2 Utils::metersToPixels(glm::vec2 meterPos)
	{
		return { meterPos.x * settings::PPM, meterPos.y * settings::PPM };
	}
}
