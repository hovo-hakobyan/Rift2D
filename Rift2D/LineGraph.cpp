#include "LineGraph.h"

#include "../3rdParty/implot/implot.h"

rift2d::LineGraph::LineGraph(GameObject* owner):
BaseComponent(owner)
{
}

void rift2d::LineGraph::onImGui()
{
	if (ImPlot::BeginPlot("My Plot")) {
		float x_data[] = { 1, 2, 3, 4, 5 };
		float y_data[] = { 1, 4, 9, 16, 25 };

		ImPlot::PlotLine("My Line Plot", x_data, y_data, 5);
		ImPlot::EndPlot();
	}
}
