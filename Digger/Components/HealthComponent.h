#pragma once
#include "BaseComponent.h"
#include "Subject.h"

namespace  digger
{
	class HealthComponent : public rift2d::BaseComponent
	{
	public:
		HealthComponent(rift2d::GameObject* owner,int maxHealth);
		virtual ~HealthComponent() override = default;
		HealthComponent(const HealthComponent& other) = delete;
		HealthComponent(HealthComponent&& other) = delete;
		HealthComponent& operator=(const HealthComponent& other) = delete;
		HealthComponent& operator=(HealthComponent&& other) = delete;

		void modify(int amount);
		bool isDead() const { return m_isDead; }
		int getMaxHealth() const { return m_maxHealth; }
		int getCurrentHealth() const { return m_currentHealth; }

		rift2d::Subject<int>* healthChangedEvent() const { return m_pOnHealthChanged.get(); }
		rift2d::Subject<int>* damageTakenEvent() const { return m_pOnDamageTaken.get(); }

		void init() override;
		void end() override;

	private:
		int m_maxHealth{};
		int m_currentHealth{};
		bool m_isDead{};

		std::unique_ptr<rift2d::Subject<int>> m_pOnHealthChanged;
		std::unique_ptr<rift2d::Subject<int>> m_pOnDamageTaken;
	};


}
