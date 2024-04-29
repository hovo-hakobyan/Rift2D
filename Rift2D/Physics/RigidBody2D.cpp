#include "RigidBody2D.h"

#include <box2d/b2_world.h>

#include "GameObject.h"
#include "Physics.h"
#include "Transform.h"

namespace rift2d
{
	RigidBody2D::RigidBody2D(GameObject* owner, RiftBodyType bodyType) :
		BaseComponent(owner),
		m_bodyType(bodyType)
	{}

	void RigidBody2D::init()
	{
		BaseComponent::init();

		auto& pWorld = Physics::GetInstance().getWorld();
		const auto transform = getOwner()->getTransform();
		const auto pos = transform->getWorldPosition();

		b2BodyDef bodyDef;
		bodyDef.type = RiftToBox2DBody(m_bodyType);
		bodyDef.position.Set(pos.x, pos.y);
		bodyDef.angle = 0.f;

		m_pBody = pWorld.CreateBody(&bodyDef);
	}

	void RigidBody2D::update()
	{
		const auto newPos = m_pBody->GetPosition();
		const auto transform = getOwner()->getTransform();
		transform->setWorldPosition(newPos.x, newPos.y);
	}

	void* RigidBody2D::getBody() const
	{
		return m_pBody;
	}

	b2BodyType RigidBody2D::RiftToBox2DBody(RiftBodyType type)
	{
		switch (type)
		{
		case RiftBodyType::Static: return b2_staticBody;
		case RiftBodyType::Dynamic: return b2_dynamicBody;
		case RiftBodyType::Kinematic:return b2_kinematicBody;
		}
		return b2_staticBody;
	}
}
