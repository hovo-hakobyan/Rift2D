#pragma once
#include <glm/vec2.hpp>


namespace rift2d
{
	class Utils
	{
	public:
		static glm::vec2 pixelToMeters(const glm::vec2& pixelPos);
		static glm::vec2 metersToPixels(const glm::vec2& meterPos);
		static int indexFromPosition(int x, int y, int nrCols);
	};

}
