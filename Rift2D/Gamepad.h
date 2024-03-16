#pragma once
#include <memory>
#include <glm/vec2.hpp>

namespace rift2d
{
	class Gamepad final
	{
	public:
		explicit Gamepad(unsigned int id);
		~Gamepad();
		Gamepad(const Gamepad& other) = delete;
		Gamepad(Gamepad&& other) = delete;
		Gamepad& operator=(const Gamepad& other) = delete;
		Gamepad& operator=(Gamepad&& other) = delete;

		void setDeadZone(float deadZone);

		void update();
		bool isDown(unsigned int button) const;
		bool isPressed(unsigned int button) const;
		bool isUp(unsigned int button) const;
		bool isStateChanged() const;

		glm::vec2 getThumbL2D() const;
		glm::vec2 getThumbR2D() const;
		glm::vec2 getDPad2D() const;
		

	private:
		class Impl;
		std::unique_ptr<Impl> m_pimpl;
	};


}
