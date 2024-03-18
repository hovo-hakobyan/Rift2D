#pragma once
#include <glm/vec2.hpp>
#include "Interfaces.h"

namespace  rift2d
{
	class Axis2DCommand : public rift2d::ICommand
	{

	public:
	    virtual ~Axis2DCommand() override = default;
	    virtual void execute() override = 0;
		virtual void setAxisValue(const glm::vec2& value) { m_axisValue = value; }
	protected:
		glm::vec2 getAxis() const { return m_axisValue; }
	private:
		glm::vec2 m_axisValue{};
	};
	
}

