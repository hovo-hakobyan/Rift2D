#pragma once
#include "BaseComponent.h"

namespace rift2d
{
	class StateComponent final : public BaseComponent
	{
	public:
		StateComponent(GameObject* owner);
		virtual ~StateComponent() override;
		StateComponent(const StateComponent& other) = delete;
		StateComponent(StateComponent&& other) = delete;
		StateComponent& operator=(const StateComponent& other) = delete;
		StateComponent& operator=(StateComponent&& other) = delete;

		void changeState(std::unique_ptr<IState> newState);
		void update() override;

		IState* getCurrentState() const { return m_pCurrentState.get(); }
		
	private:
		std::unique_ptr<IState> m_pCurrentState;
	};

}
