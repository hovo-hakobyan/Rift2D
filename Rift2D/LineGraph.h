#pragma once
#include "BaseComponent.h"

namespace rift2d
{
	class LineGraph final : public rift2d::BaseComponent
	{
	public:
		LineGraph(GameObject* owner);
		virtual ~LineGraph() override = default;
		LineGraph(const LineGraph& other) = delete;
		LineGraph(LineGraph&& other) = delete;
		LineGraph& operator=(const LineGraph& other) = delete;
		LineGraph& operator=(LineGraph&& other) = delete;

	private:

	};
}


