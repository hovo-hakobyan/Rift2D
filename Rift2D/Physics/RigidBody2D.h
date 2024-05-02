#pragma once
#include <glm/vec2.hpp>
#include "BaseComponent.h"

namespace rift2d
{
	enum class RiftBodyType
	{
		Static = 0,
		Dynamic = 1,
		Kinematic = 2
	};

	struct RigidBodyDef
	{
		RiftBodyType type;
		glm::vec2 pos;
		bool fixedRotation;
		float linearDamping = 0.1f;

	};

	class RigidBody2D final : public BaseComponent
	{
	public:
		RigidBody2D(GameObject* owner, RigidBodyDef bodyDef);
		virtual ~RigidBody2D() override;
		RigidBody2D(const RigidBody2D& other) = delete;
		RigidBody2D(RigidBody2D&& other) = delete;
		RigidBody2D& operator=(const RigidBody2D& other) = delete;
		RigidBody2D& operator=(RigidBody2D&& other) = delete;

		virtual void init() override;
		void update() override;
		void setLinearVelocity(const glm::vec2 v) const;
		void setLinearDamping(float damping) const;
		void applyLinearImpulse(const glm::vec2 impulse, const glm::vec2 point) const;
		void setRotation(const glm::vec2 dir) const;

		void* getBody() const;
	private:
		class Impl;
		std::unique_ptr<Impl> m_pImpl;

	};


}
