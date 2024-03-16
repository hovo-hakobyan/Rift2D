#include <SDL.h>
#include "InputManager.h"
#include "backends/imgui_impl_sdl2.h"

void rift2d::InputManager::init()
{
	m_gamepads.reserve(XUSER_MAX_COUNT);
	m_actionBindings.reserve(XUSER_MAX_COUNT * 14);
	m_axisBinding2Ds.reserve(XUSER_MAX_COUNT * 2);
	for (DWORD i = 0; i < XUSER_MAX_COUNT; ++i) 
	{
		m_gamepads.push_back(std::make_unique<Gamepad>(i));
	}
}

bool rift2d::InputManager::processInput()
{

	for(const auto& gamepad : m_gamepads)
	{
		gamepad->update();
	}

	//process input actions
	for(const auto& action : m_actionBindings)
	{
		if(const auto gamepad = m_gamepads[action.gamepadId].get())
		{
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

	for(const auto& axisEvent: m_axisBinding2Ds)
	{
		if(const auto gamepad = m_gamepads[axisEvent.gamepadId].get())
		{
			bool shouldExecute = false;
			glm::vec2 axisVal{0.f,0.f};
			switch(axisEvent.axis2D)
			{
			case GamepadAxis2D::LThumbStick:
				axisVal = gamepad->getThumbL2D();
				shouldExecute = true;
				break;
			case GamepadAxis2D::RThumbStick:
				axisVal = gamepad->getThumbR2D();
				break;
			}

			if (!shouldExecute) continue;
			if (std::abs(axisVal.x) > 0.f || std::abs(axisVal.y) > 0.0f)
			{
				axisEvent.command->setAxisValue(axisVal);
				axisEvent.command->execute();
			}

		}
	}

	SDL_Event e;
	while (SDL_PollEvent(&e)) {
		if (e.type == SDL_QUIT) {
			return false;
		}
		if (e.type == SDL_KEYDOWN) {
			
		}
		if (e.type == SDL_MOUSEBUTTONDOWN) {
			
		}
		// etc...

		ImGui_ImplSDL2_ProcessEvent(&e);
	}

	return true;
}

void rift2d::InputManager::bindAction(GamepadKey key, unsigned int gamepadId, InputEvent event,
	std::unique_ptr<ICommand> command)
{
	m_actionBindings.push_back({ key,gamepadId,event,std::move(command) });
}

void rift2d::InputManager::bindAxis2D(GamepadAxis2D axis, unsigned gamepadId, std::unique_ptr<Axis2DCommand> command)
{
	m_axisBinding2Ds.push_back({ axis,gamepadId,std::move(command) });
}

