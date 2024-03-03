#pragma once
#include "BaseComponent.h"

namespace rift2d
{
	class TextComponent;
	class FPSComponent final : public BaseComponent, public IComponentWatcher
	{
	public:
		virtual void init() override;
		virtual void update() override;
		virtual void end() override;

		FPSComponent(GameObject* owner);
		virtual ~FPSComponent() override = default;
		FPSComponent(const FPSComponent& other) = delete;
		FPSComponent(FPSComponent&& other) = delete;
		FPSComponent& operator=(const FPSComponent& other) = delete;
		FPSComponent& operator=(FPSComponent&& other) = delete;

		virtual void onComponentRemoved(BaseComponent* component);
		void test(std::shared_ptr<GameObject> t, std::shared_ptr<GameObject> l) { textObj = t; logoObj = l; }

	private:
		TextComponent* m_pText{};
		float m_accumulatedSeconds{0.0f};
		int m_frameCount{};
		float m_updateInterval{ 2.1f };
		std::weak_ptr<GameObject> textObj;
		std::weak_ptr<GameObject> logoObj;
	};

}

