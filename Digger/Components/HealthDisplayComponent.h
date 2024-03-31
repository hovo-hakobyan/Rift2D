#pragma once
#include <vector>
#include "BaseComponent.h"


namespace rift2d
{
	class SpriteComponent;
}

namespace digger
{
	class HealthComponent;
	class HealthDisplayComponent : public rift2d::BaseComponent, public rift2d::IComponentWatcher
	{
	public:
		HealthDisplayComponent(rift2d::GameObject* owner, HealthComponent* healthComponent);
		virtual ~HealthDisplayComponent() override = default;
		HealthDisplayComponent(const HealthDisplayComponent& other) = delete;
		HealthDisplayComponent(HealthDisplayComponent&& other) = delete;
		HealthDisplayComponent& operator=(const HealthDisplayComponent& other) = delete;
		HealthDisplayComponent& operator=(HealthDisplayComponent&& other) = delete;

		void init() override;
		void end() override;

		virtual void onComponentRemoved(rift2d::BaseComponent* component) override;
	private:
		std::vector<rift2d::SpriteComponent*> m_pSpriteComponents{};
		HealthComponent* m_pHealth;
		unsigned int m_observerId{};

		void updateLivesDisplay(int currentLives);
	};


}
