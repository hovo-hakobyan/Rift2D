#pragma once
#include <vector>

#include "BaseComponent.h"

namespace rift2d
{
	class LineGraph final : public BaseComponent
	{
	public:
		LineGraph(GameObject* owner,std::string name);
		virtual ~LineGraph() override = default;
		LineGraph(const LineGraph& other) = delete;
		LineGraph(LineGraph&& other) = delete;
		LineGraph& operator=(const LineGraph& other) = delete;
		LineGraph& operator=(LineGraph&& other) = delete;

		virtual void onImGui() override;

		void setShouldPlot(bool shouldPlot) { m_shouldPlot = shouldPlot; }
		bool isPlotting() const { return m_shouldPlot; }
		void addDataPoint(size_t lineIndex, float xVal, float yVal);
		void addDataPoints(size_t lineIndex, const std::vector<float>& xVals, const std::vector<float>& yVals);
		void addLine(const std::string& lineName); 
		void clearData(size_t lineIndex); 
		void clearAll();

		std::vector<float> getDataX(size_t lineIndex);
		std::vector<float> getDataY(size_t lineIndex);
	private:
		bool m_shouldPlot{};
		std::vector<std::vector<float>> m_dataX;
		std::vector<std::vector<float>> m_dataY;
		std::vector<std::string> m_lineNames;
		std::string m_name;
	};
}


