#pragma once
#include <memory>
#include <glm/vec2.hpp>

namespace rift2d
{
	enum class GamepadKey
	{
		DPad_Up = 0x0001,
		DPad_Down = 0x0002,
		DPad_Left = 0x0004,
		DPad_Right = 0x0008,
		Start = 0x0010,
		Back = 0x0020,
		LThumb = 0x0040,
		RThumb = 0x0080,
		LShoulder = 0x0100,
		RShoulder = 0x0200,
		A = 0x1000,
		B = 0x2000,
		X = 0x4000,
		Y = 0x8000,
	};

	enum class GamepadAxis2D
	{
		LThumbStick,
		RThumbStick,
		DPad
	};


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

		static int getMaxUsers();

		glm::vec2 getThumbL2D() const;
		glm::vec2 getThumbR2D() const;
		glm::vec2 getDPad2D() const;
		

	private:
		class Impl;
		std::unique_ptr<Impl> m_pimpl;
	};


}
