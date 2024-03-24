#pragma once
#include <vector>
#include "Axis2DCommand.h"
#include "Gamepad.h"
#include "Singleton.h"
#include <SDL.h>

namespace rift2d
{
	enum class InputEvent
	{
		Down, Up, Pressed
	};

	class InputManager final : public Singleton<InputManager>
	{
	public:
		void init();
		bool processInput();
		ICommand* bindAction(GamepadKey key, unsigned int gamepadId,InputEvent event, std::unique_ptr<ICommand> command);
		ICommand* bindAction(SDL_KeyCode keyboardKey, InputEvent event, std::unique_ptr<ICommand> command);
		ICommand* bindAxis2D(GamepadAxis2D axis2D, unsigned int gamepadId, std::unique_ptr<Axis2DCommand> command);
		ICommand* bindAxis2D(SDL_Scancode x, SDL_Scancode y, SDL_Scancode xNegative, SDL_Scancode yNegative, std::unique_ptr<Axis2DCommand> command);

		void unbindCommand(ICommand* command);

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
			SDL_KeyCode key;
			InputEvent event;
			std::unique_ptr<ICommand> command;
			bool shouldExecute = false;
		};

		struct KeyboardAxis2DBinding
		{
			SDL_Scancode x;
			SDL_Scancode y;
			SDL_Scancode xNegative;
			SDL_Scancode yNegative;
			std::unique_ptr<Axis2DCommand> command;
		};

		std::vector<GamepadActionBinding> m_gamepadActionBindings;
		std::vector<GamepadAxisBinding2D> m_gamepadAxis2DBindings;
		std::vector<KeyboardActionBinding> m_keyboardActionBindings;
		std::vector<KeyboardAxis2DBinding> m_keyboardAxis2DBindings;

		std::vector<std::unique_ptr<Gamepad>> m_gamepads;
		std::vector<bool> m_keyStatesSDL;

		void processGamepadActions() const;
		void processGamepadAxis() const;
		void processKeyboardAxis() const;
		void processKeyboardActions();
		bool processSDL();
	};

}
