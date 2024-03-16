#pragma once
#include <glm/vec2.hpp>
#include "Interfaces.h"

namespace  rift2d
{
	class Axis2DCommand : public rift2d::ICommand
	{
	protected:
	    glm::vec2 m_axisValue{};

	public:
		Axis2DCommand(GameObject* obj): ICommand(obj){}
	    virtual ~Axis2DCommand() override = default;
	    virtual void execute() override = 0;
		virtual void setAxisValue(const glm::vec2& value) { m_axisValue = value; }
	};
	
}

