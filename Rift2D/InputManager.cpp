
#include "InputManager.h"
#include <iostream>
#include "GameObject.h"
#include "backends/imgui_impl_sdl2.h"

void rift2d::InputManager::init()
{
	m_gamepads.reserve(XUSER_MAX_COUNT);
	for (DWORD i = 0; i < XUSER_MAX_COUNT; ++i) 
	{
		m_gamepads.push_back(std::make_unique<Gamepad>(i));
	}
	m_keyStatesSDL.resize(SDL_NUM_SCANCODES, false);
}

bool rift2d::InputManager::processInput()
{

	for(const auto& gamepad : m_gamepads)
	{
		gamepad->update();
	}

	processGamepadAxis();
	processGamepadActions();

	if (!processSDL()) return false;
	processKeyboardAxis();
	processKeyboardActions();

	return true;
	
}

rift2d::ICommand* rift2d::InputManager::bindAction(GamepadKey key, unsigned int gamepadId, InputEvent event,
                                                   std::unique_ptr<ICommand> command)
{
	auto rawPtr = command.get();
	m_gamepadActionBindings.push_back({ key,gamepadId,event,std::move(command) });
	return rawPtr;
}

rift2d::ICommand* rift2d::InputManager::bindAction(SDL_KeyCode keyboardKey, InputEvent event, std::unique_ptr<ICommand> command)
{
	auto rawPtr = command.get();
	m_keyboardActionBindings.push_back({ keyboardKey,event,std::move(command) });
	return rawPtr;
}

rift2d::ICommand* rift2d::InputManager::bindAxis2D(GamepadAxis2D axis, unsigned gamepadId, std::unique_ptr<Axis2DCommand> command)
{
	auto rawPtr = command.get();
	m_gamepadAxis2DBindings.push_back({ axis,gamepadId,std::move(command) });
	return rawPtr;
}

rift2d::ICommand* rift2d::InputManager::bindAxis2D(SDL_Scancode x, SDL_Scancode y, SDL_Scancode xNegative, SDL_Scancode yNegative,
                                                   std::unique_ptr<Axis2DCommand> command)
{
	auto rawPtr = command.get();
	m_keyboardAxis2DBindings.push_back({ x,y,xNegative,yNegative,std::move(command) });
	return rawPtr;
}

void rift2d::InputManager::unbindCommand(ICommand* command)
{
	if (!command) return;

	auto removeCommand = [command](auto& bindings)
	{
		auto it = std::remove_if(bindings.begin(), bindings.end(),
			[command](const auto& binding)
			{
				return binding.command.get() == command;
			});
		bindings.erase(it, bindings.end());
		};

	removeCommand(m_gamepadActionBindings);
	removeCommand(m_gamepadAxis2DBindings);
	removeCommand(m_keyboardAxis2DBindings);
	removeCommand(m_keyboardActionBindings);
}



void rift2d::InputManager::processGamepadActions() const
{
	//process input actions
	for (const auto& action : m_gamepadActionBindings)
	{
		if (const auto gamepad = m_gamepads[action.gamepadId].get())
		{
			if (!gamepad->isStateChanged()) continue;
			
			bool shouldExecute = false;
			switch (action.event)
			{
			case InputEvent::Down:
				if (gamepad->isDown(static_cast<unsigned int>(action.key))) shouldExecute = true;
				break;
			case InputEvent::Up:
				if (gamepad->isUp(static_cast<unsigned int>(action.key))) shouldExecute = true;
				break;
			case InputEvent::Pressed:
				if (gamepad->isPressed(static_cast<unsigned int>(action.key))) shouldExecute = true;
				break;
			}

			if (shouldExecute) action.command->execute();
		}
	}
}

void rift2d::InputManager::processGamepadAxis() const
{
	//process input axis
	for (const auto& axisBinding2D : m_gamepadAxis2DBindings)
	{
		if (const auto gamepad = m_gamepads[axisBinding2D.gamepadId].get())
		{
			bool shouldExecute = false;
			glm::vec2 axisVal{ 0.f,0.f };
			switch (axisBinding2D.axis2D)
			{
			case GamepadAxis2D::LThumbStick:
				axisVal = gamepad->getThumbL2D();
				shouldExecute = true;
				break;
			case GamepadAxis2D::RThumbStick:
				axisVal = gamepad->getThumbR2D();
				shouldExecute = true;
				break;
			case GamepadAxis2D::DPad:
				axisVal = gamepad->getDPad2D();
				shouldExecute = true;
				break;
			}

			if (!shouldExecute) continue;
			if (std::abs(axisVal.x) > 0.f || std::abs(axisVal.y) > 0.0f)
			{
				axisBinding2D.command->setAxisValue(axisVal);
				axisBinding2D.command->execute();
			}

		}
	}
}

void rift2d::InputManager::processKeyboardAxis() const
{
	for (const auto& keyboardAxis2DBinding : m_keyboardAxis2DBindings)
	{
		glm::vec2 axis{};
		bool shouldExecute{};
		if (m_keyStatesSDL[keyboardAxis2DBinding.x])
		{
			axis.x = 1.f;
			shouldExecute = true;
		}
		else if (m_keyStatesSDL[keyboardAxis2DBinding.xNegative])
		{
			axis.x = -1.f;
			shouldExecute = true;
		}

		if (m_keyStatesSDL[keyboardAxis2DBinding.y])
		{
			axis.y = 1.f;
			shouldExecute = true;
		}
		else if (m_keyStatesSDL[keyboardAxis2DBinding.yNegative])
		{
			axis.y = -1.f;
			shouldExecute = true;
		}

		if (!shouldExecute) continue;
		keyboardAxis2DBinding.command->setAxisValue(axis);
		keyboardAxis2DBinding.command->execute();
	}
}

void rift2d::InputManager::processKeyboardActions() 
{
	for (auto& keyboardActionBinding : m_keyboardActionBindings)
	{
		if(keyboardActionBinding.shouldExecute)
		{
			keyboardActionBinding.command->execute();
			keyboardActionBinding.shouldExecute = false;
		}
	}
}

bool rift2d::InputManager::processSDL()
{
	SDL_Event e;
	while (SDL_PollEvent(&e))
	{
		if (e.type == SDL_QUIT)
		{
			return false;
		}
		if (e.type == SDL_KEYDOWN)
		{
			m_keyStatesSDL[e.key.keysym.scancode] = true;
			if (e.key.repeat == 0)
			{
				for (auto& keyboardActionBinding : m_keyboardActionBindings)
				{
					if (keyboardActionBinding.event == InputEvent::Down && e.key.keysym.sym == keyboardActionBinding.key)
						keyboardActionBinding.shouldExecute = true;
				}
			}
		}
		if (e.type == SDL_KEYUP) 
		{
			m_keyStatesSDL[e.key.keysym.scancode] = false;
			if (e.key.repeat == 0)
			{
				for (auto& keyboardActionBinding : m_keyboardActionBindings)
				{
					if (keyboardActionBinding.event == InputEvent::Up && e.key.keysym.sym == keyboardActionBinding.key)
						keyboardActionBinding.shouldExecute = true;
				}
			}
		}

		ImGui_ImplSDL2_ProcessEvent(&e);
	}

	return true;
}

