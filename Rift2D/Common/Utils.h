#pragma once
#include <glm/vec2.hpp>


namespace rift2d
{
	class Utils
	{
	public:
		static glm::vec2 pixelToMeters(glm::vec2 pixelPos);
		static glm::vec2 metersToPixels(glm::vec2 meterPos);
	};

}
