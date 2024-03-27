#include "LineGraph.h"

#include "implot.h"

rift2d::LineGraph::LineGraph(GameObject* owner,std::string name):
BaseComponent(owner), m_name(std::move(name))
{
}

void rift2d::LineGraph::onImGui()
{
	if (!m_shouldPlot) return;
	ImGui::Begin("Plot");
	ImGui::SetNextWindowSize(ImVec2(400, 400), ImGuiCond_FirstUseEver);
	if(ImGui::BeginChild("Plot Child Window"))
	{

		
		if (ImPlot::BeginPlot(m_name.c_str()))
		{
			for (size_t i = 0; i < m_dataX.size() && i < m_dataY.size(); ++i)
			{
				if (!m_dataX[i].empty() && m_dataX[i].size() == m_dataY[i].size())
				{

					ImPlot::PlotLine(m_lineNames[i].c_str(), m_dataX[i].data(), m_dataY[i].data(), static_cast<int>(m_dataX[i].size()));
				}
			}
			ImPlot::EndPlot();
		}
	}
	ImGui::EndChild();
	ImGui::End();
	
}

void rift2d::LineGraph::addDataPoint(size_t lineIndex, float xVal, float yVal)
{
	if (lineIndex < m_dataX.size() && lineIndex < m_dataY.size())
	{
		m_dataX[lineIndex].push_back(xVal);
		m_dataY[lineIndex].push_back(yVal);
	}
}

void rift2d::LineGraph::addDataPoints(size_t lineIndex, const std::vector<float>& xVals,
	const std::vector<float>& yVals)
{
	if (lineIndex < m_dataX.size() && lineIndex < m_dataY.size() && xVals.size() == yVals.size())
	{
		m_dataX[lineIndex].insert(m_dataX[lineIndex].end(), xVals.begin(), xVals.end());
		m_dataY[lineIndex].insert(m_dataY[lineIndex].end(), yVals.begin(), yVals.end());
	}
}

void rift2d::LineGraph::addLine(const std::string& lineName)
{
	m_lineNames.push_back(lineName);
	m_dataX.push_back({});
	m_dataY.push_back({});
}

void rift2d::LineGraph::clearData(size_t lineIndex)
{
	if (lineIndex < m_dataX.size() && lineIndex < m_dataY.size())
	{
		m_dataX[lineIndex].clear();
		m_dataY[lineIndex].clear();
	}
}


void rift2d::LineGraph::clearAll()
{
	
	for (auto& dataSeries : m_dataX) {
		dataSeries.clear();
	}
	m_dataX.clear();

	for (auto& dataSeries : m_dataY) {
		dataSeries.clear();
	}
	m_dataY.clear(); 

	m_lineNames.clear();
}

std::vector<float> rift2d::LineGraph::getDataX(size_t lineIndex)
{
	if (lineIndex < m_dataX.size()) return m_dataX[lineIndex];
	return {};
}

std::vector<float> rift2d::LineGraph::getDataY(size_t lineIndex)
{
	if (lineIndex < m_dataY.size()) return m_dataY[lineIndex];
	return {};
}
