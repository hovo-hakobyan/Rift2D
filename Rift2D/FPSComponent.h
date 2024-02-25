#pragma once
#include "BaseComponent.h"

namespace rift2d
{
	class TextComponent;
	class FPSComponent final : public BaseComponent
	{
	public:
		virtual void Init() override;
		virtual void Update() override;
		virtual void FixedUpdate() {}

		FPSComponent(std::shared_ptr<GameObject> owner);
		virtual ~FPSComponent() = default;
		FPSComponent(const FPSComponent& other) = delete;
		FPSComponent(FPSComponent&& other) = delete;
		FPSComponent& operator=(const FPSComponent& other) = delete;
		FPSComponent& operator=(FPSComponent&& other) = delete;

	private:
		std::weak_ptr<TextComponent> m_pText;
		float m_AccumulatedSeconds{0.0f};
		int m_FrameCount{};
		float m_UpdateInterval{ .1f };
	};

}

