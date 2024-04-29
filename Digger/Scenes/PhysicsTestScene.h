#pragma once
#include "Scene.h"

namespace digger
{
	class PhysicsTestScene : public rift2d::Scene
	{
	public:
		PhysicsTestScene();
		~PhysicsTestScene() override = default;
		PhysicsTestScene(const PhysicsTestScene& other) = delete;
		PhysicsTestScene(PhysicsTestScene&& other) noexcept = delete;
		PhysicsTestScene& operator=(const PhysicsTestScene& other) = delete;
		PhysicsTestScene& operator=(PhysicsTestScene&& other) noexcept = delete;

	protected:

		virtual void init() override;
	};


}
