#pragma once
#include <vector>
#include "Gamepad.h"
#include "Singleton.h"
#include <SDL_scancode.h>
#include "Axis2DCommand.h"

namespace rift2d
{
	enum class InputEvent
	{
		Down, Up, Pressed
	};


	class InputManager final : public Singleton<InputManager>
	{
	public:
		~InputManager() override;
		void init();
		bool processInput();
		ICommand* bindAction(GamepadKey key, unsigned int gamepadId,InputEvent event, std::unique_ptr<ICommand> command, bool isPersistent = false, GameObject* pOwner = nullptr);
		ICommand* bindAction(SDL_Scancode keyboardKey, InputEvent event, std::unique_ptr<ICommand> command, bool isPersistent = false, GameObject* pOwner = nullptr);
		ICommand* bindAxis2D(GamepadAxis2D axis2D, unsigned int gamepadId, std::unique_ptr<Axis2DCommand> command, bool isPersistent = false, GameObject* pOwner = nullptr);
		ICommand* bindAxis2D(SDL_Scancode x, SDL_Scancode y, SDL_Scancode xNegative, SDL_Scancode yNegative, std::unique_ptr<Axis2DCommand> command, bool isPersistent = false, GameObject* pOwner = nullptr);

		void unbindCommand(ICommand* command);
		void unbindNonPersistentCommands();

		void disableInput() { m_isDisabled = true; }
		void enableInput() { m_isDisabled = false; }

	private:
		struct GamepadActionBinding
		{
			GamepadKey key;
			unsigned int gamepadId;
			InputEvent event;
			std::unique_ptr<ICommand> command;
			bool isPersistent;

		};

		struct GamepadAxisBinding2D
		{
			GamepadAxis2D axis2D;
			unsigned int gamepadId;
			std::unique_ptr<Axis2DCommand> command;
			bool isPersistent;
		};

		struct KeyboardActionBinding
		{
			SDL_Scancode key;
			InputEvent event;
			std::unique_ptr<ICommand> command;
			bool shouldExecute = false;
			bool isPersistent;
		};

		struct KeyboardAxis2DBinding
		{
			SDL_Scancode x;
			SDL_Scancode y;
			SDL_Scancode xNegative;
			SDL_Scancode yNegative;
			std::unique_ptr<Axis2DCommand> command;
			bool isPersistent;
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
		void registerInputOwner(GameObject* pOwner);

		bool m_isDisabled{false};
	};

}
