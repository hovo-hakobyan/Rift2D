#pragma once
#include <glm/glm.hpp>

namespace rift2d
{
	class Transform final
	{
	public:
		const glm::vec3& getPosition() const { return m_position; }
		void setPosition(float x, float y, float z);
	private:
		glm::vec3 m_position{};
	};
}
