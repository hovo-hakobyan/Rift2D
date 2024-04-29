#pragma once
#include <box2d/b2_body.h>

#include "BaseComponent.h"

namespace rift2d
{
	class RigidBody2D final : public BaseComponent
	{
	public:
		enum class RiftBodyType
		{
			Static = 0,
			Dynamic = 1,
			Kinematic = 2
		};

		RigidBody2D(GameObject* owner, RiftBodyType bodyType);
		virtual ~RigidBody2D() override = default;
		RigidBody2D(const RigidBody2D& other) = delete;
		RigidBody2D(RigidBody2D&& other) = delete;
		RigidBody2D& operator=(const RigidBody2D& other) = delete;
		RigidBody2D& operator=(RigidBody2D&& other) = delete;

		virtual void init() override;
		void update() override;
		void* getBody() const;
	private:
		RiftBodyType m_bodyType;
		b2Body* m_pBody;

		static b2BodyType RiftToBox2DBody(RiftBodyType type);
	};


}
