#include "Gamepad.h"
#include <format>
#include <iostream>
#include <SDL_syswm.h>

#include "InputManager.h"


rift2d::Gamepad::Gamepad(unsigned int id): m_id{id}
{
}

void rift2d::Gamepad::setDeadZone(float deadZone)
{
    if (deadZone < 0.f)
    {
        m_deadZone = 0.f;
        return;
    }

    if(deadZone > 1.f)
    {
        m_deadZone = 1.f;
        return;
    }

    m_deadZone = deadZone;
       
}

void rift2d::Gamepad::update()
{
    CopyMemory(&m_previousState, &m_currentState, sizeof(XINPUT_STATE));
    ZeroMemory(&m_currentState, sizeof(XINPUT_STATE));
    const DWORD dwResult = XInputGetState(m_id, &m_currentState);

    if (dwResult == ERROR_DEVICE_NOT_CONNECTED)
    {
        m_isConnected = false;
		return;
    }
    m_isConnected = true;

    const auto buttonChanges = m_currentState.Gamepad.wButtons ^ m_previousState.Gamepad.wButtons;
    buttonsPressedThisFrame = buttonChanges & m_currentState.Gamepad.wButtons;
	buttonsReleasedThisFrame = buttonChanges & (~m_currentState.Gamepad.wButtons);
}

bool rift2d::Gamepad::isDown(unsigned button) const
{
    return buttonsPressedThisFrame & button;
}

bool rift2d::Gamepad::isPressed(unsigned button) const
{
    return m_currentState.Gamepad.wButtons & button;
}

bool rift2d::Gamepad::isUp(unsigned button) const
{
    return buttonsReleasedThisFrame & button;
}

glm::vec2 rift2d::Gamepad::getThumbL2D() const
{
	const float deadzoneThreshold = m_deadZone * 32767;

    const float x = std::abs(m_currentState.Gamepad.sThumbLX) < deadzoneThreshold ? 0.0f : m_currentState.Gamepad.sThumbLX / 32767.0f;
    const float y = std::abs(m_currentState.Gamepad.sThumbLY) < deadzoneThreshold ? 0.0f : m_currentState.Gamepad.sThumbLY / 32767.0f;

    return glm::vec2{ x, -1.f * y };
}

glm::vec2 rift2d::Gamepad::getThumbR2D() const
{
	const float deadzoneThreshold = m_deadZone * 32767;

    const float x = std::abs(m_currentState.Gamepad.sThumbRX) < deadzoneThreshold ? 0.0f : m_currentState.Gamepad.sThumbRX / 32767.0f;
	const float y = std::abs(m_currentState.Gamepad.sThumbRY) < deadzoneThreshold ? 0.0f : m_currentState.Gamepad.sThumbRY / 32767.0f;

    return glm::vec2{ x,-1.f * y };
}

glm::vec2 rift2d::Gamepad::getDPad2D() const
{
    glm::vec2 axis{};
    if (isPressed(static_cast<unsigned int>(rift2d::GamepadKey::DPad_Left))) axis.x = -1.f;
    else if (isPressed(static_cast<unsigned int>(rift2d::GamepadKey::DPad_Right))) axis.x = 1.0f;

    if (isPressed(static_cast<unsigned int>(rift2d::GamepadKey::DPad_Down))) axis.y = 1.f;
    else if (isPressed(static_cast<unsigned int>(rift2d::GamepadKey::DPad_Up))) axis.y = -1.0f;

    return axis;
}
