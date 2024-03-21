#pragma once
#include "BaseComponent.h"
#include "Subject.h"

namespace rift2d
{
	class SpriteComponent;
}

namespace  rift2d
{
	class HealthComponent : public BaseComponent
	{
	public:
		HealthComponent(GameObject* owner,int maxHealth);
		virtual ~HealthComponent() override = default;
		HealthComponent(const HealthComponent& other) = delete;
		HealthComponent(HealthComponent&& other) = delete;
		HealthComponent& operator=(const HealthComponent& other) = delete;
		HealthComponent& operator=(HealthComponent&& other) = delete;

		void modify(int amount);
		bool isDead() const { return m_isDead; }
		int getMaxHealth() const { return m_maxHealth; }
		int getCurrentHealth() const { return m_currentHealth; }

		Subject<int>* healthChangedEvent() const { return m_pHealthChanged.get(); }

		void init() override;

	private:
		int m_maxHealth{};
		int m_currentHealth{};
		bool m_isDead{};

		std::unique_ptr<Subject<int>> m_pHealthChanged;
	};


}
