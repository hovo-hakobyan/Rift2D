#pragma once
#include <tuple>
#include <glm/vec2.hpp>


namespace rift2d
{
	class Utils
	{
	public:
		static glm::vec2 pixelToMeters(const glm::vec2& pixelPos);
		static glm::vec2 metersToPixels(const glm::vec2& meterPos);
		static int indexFromPosition(int x, int y, int nrCols);
		static int indexFromRowsCols(int row, int col, int nrCols);
		static std::tuple<int, int> getRowColIdx(const glm::vec2& pos);
		static glm::vec2 positionFromRowCol(int row, int col);
	};

}
