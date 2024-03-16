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
		void bindAction(unsigned int keyboardKey, InputEvent event, std::unique_ptr<ICommand> command);
		void bindAxis2D(GamepadAxis2D axis2D, unsigned int gamepadId, std::unique_ptr<Axis2DCommand> command);
		void bindAxis2D(int x,  int y, int xNegative, int yNegative, std::unique_ptr<Axis2DCommand> command);

	private:
		struct GamepadActionBinding
		{
			GamepadKey key;
			unsigned int gamepadId;
			InputEvent event;
			std::unique_ptr<ICommand> command;
		};

		struct GamepadAxisBinding2D
		{
			GamepadAxis2D axis2D;
			unsigned int gamepadId;
			std::unique_ptr<Axis2DCommand> command;
		};

		struct KeyboardActionBinding
		{
			unsigned int key;
			InputEvent event;
			std::unique_ptr<ICommand> command;
		};

		struct KeyboardAxis2DMapping
		{
			int x;
			int y;
			int xNegative;
			int yNegative;
			std::unique_ptr<Axis2DCommand> command;
		};

		std::vector<GamepadActionBinding> m_gamepadActionBindings;
		std::vector<GamepadAxisBinding2D> m_gamepadAxis2DBindings;
		std::vector<KeyboardActionBinding> m_keyboardActionBindings;
		std::vector<KeyboardAxis2DMapping> m_keyboardAxis2DBindings;
		std::vector<std::unique_ptr<Gamepad>> m_gamepads;
		std::vector<bool> m_keyStatesSDL;

		void processGamepadActions() const;
		void processGamepadAxis() const;
		void processKeyboardAxis() const;
		bool processSDL();
	};

}
