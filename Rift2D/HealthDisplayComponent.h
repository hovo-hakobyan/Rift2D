#pragma once
#include <vector>

#include "BaseComponent.h"

namespace rift2d
{
	class SpriteComponent;
	class HealthComponent;
}

namespace rift2d
{
	class HealthDisplayComponent : public BaseComponent, public IComponentWatcher
	{
	public:
		HealthDisplayComponent(GameObject* owner,HealthComponent* healthComponent);
		virtual ~HealthDisplayComponent() override = default;
		HealthDisplayComponent(const HealthDisplayComponent& other) = delete;
		HealthDisplayComponent(HealthDisplayComponent&& other) = delete;
		HealthDisplayComponent& operator=(const HealthDisplayComponent& other) = delete;
		HealthDisplayComponent& operator=(HealthDisplayComponent&& other) = delete;

		void init() override;

		virtual void onComponentRemoved(BaseComponent* component) override;
	private:
		std::vector<SpriteComponent*> m_pSpriteComponents{};
		HealthComponent* m_pHealth;
		unsigned int m_observerId{};

		void updateLivesDisplay(int currentLives);
	};


}
