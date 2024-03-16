#pragma once
#include <memory>
#include <vector>
#include "Axis2DCommand.h"
#include "Gamepad.h"
#include "Singleton.h"

namespace rift2d
{
	enum class InputEvent
	{
		Down, Up, Pressed
	};

	enum class GamepadKey : unsigned int
	{
		DPad_Up = XINPUT_GAMEPAD_DPAD_UP,
		DPad_Down = XINPUT_GAMEPAD_DPAD_DOWN,
		DPad_Left = XINPUT_GAMEPAD_DPAD_LEFT,
		DPad_Right = XINPUT_GAMEPAD_DPAD_RIGHT,
		Start = XINPUT_GAMEPAD_START,
		Back = XINPUT_GAMEPAD_BACK,
		LThumb = XINPUT_GAMEPAD_LEFT_THUMB,
		RThumb = XINPUT_GAMEPAD_RIGHT_THUMB,
		LShoulder = XINPUT_GAMEPAD_LEFT_SHOULDER,
		RShoulder = XINPUT_GAMEPAD_RIGHT_SHOULDER,
		A = XINPUT_GAMEPAD_A,
		B = XINPUT_GAMEPAD_B,
		X = XINPUT_GAMEPAD_X,
		Y = XINPUT_GAMEPAD_Y,
	};

	enum class GamepadAxis2D
	{
		LThumbStick,
		RThumbStick,
		DPad

	};

	class InputManager final : public Singleton<InputManager>
	{
	public:
		void init();
		bool processInput();
		void bindAction(GamepadKey key, unsigned int gamepadId,InputEvent event, std::unique_ptr<ICommand> command);
		void bindAxis2D(GamepadAxis2D axis2D, unsigned int gamepadId, std::unique_ptr<Axis2DCommand> command);

	private:
		struct ActionBinding
		{
			GamepadKey key;
			unsigned int gamepadId;
			InputEvent event;
			std::unique_ptr<ICommand> command;
		};

		struct AxisBinding2D
		{
			GamepadAxis2D axis2D;
			unsigned int gamepadId;
			std::unique_ptr<Axis2DCommand> command;
		};

		std::vector<ActionBinding> m_actionBindings;
		std::vector<AxisBinding2D> m_axisBinding2Ds;
		std::vector<std::unique_ptr<Gamepad>> m_gamepads;

		void processGamepadActions() const;
		void processGamepadAxis() const;
		bool processSDL() const;
	};

}
