#include "StateComponent.h"
namespace rift2d
{
	StateComponent::StateComponent(GameObject* owner):
	BaseComponent(owner){}

	StateComponent::~StateComponent() = default;

	void StateComponent::changeState(std::unique_ptr<IState> newState)
	{
		if(m_pCurrentState) m_pCurrentState->onExit(getOwner());

		m_pCurrentState = std::move(newState);
		if (m_pCurrentState) m_pCurrentState->onEnter(getOwner());
	}

	void StateComponent::update()
	{
		if (m_pCurrentState) m_pCurrentState->update(getOwner());
	}
}
