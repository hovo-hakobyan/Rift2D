#include "BoxCollider2D.h"

#include <box2d/b2_fixture.h>
#include <box2d/b2_polygon_shape.h>

#include "Color.h"
#include "DebugBoxComponent.h"
#include "Exception.h"
#include "GameObject.h"
#include "RigidBody2D.h"
#include "Utils.h"

namespace rift2d
{
	BoxCollider2D::BoxCollider2D(GameObject* owner, const BoxColliderInfo& info) :
		BaseComponent(owner),
		m_info(info)
	{
	}

	void BoxCollider2D::init()
	{
		BaseComponent::init();

		const auto rb = getOwner()->getComponent<RigidBody2D>();
		if(!rb)
		{
			THROW_RIFT_EXCEPTION("Box Collider cannot exist without a RigidBody2D",RiftExceptionType::Error);
		}

		b2PolygonShape shape;

		const glm::vec2 size = { Utils::pixelToMeters(m_info.size) };
		shape.SetAsBox(size.x * 0.5f, size.y * 0.5f);
		

		//Fixture is used to attach a shape to a body for collision detection
		b2FixtureDef fixtureDef;
		fixtureDef.shape = &shape;
		fixtureDef.density = m_info.density;
		fixtureDef.restitution = m_info.restitution;
		fixtureDef.restitutionThreshold = m_info.restitutionThreshold;
		const auto body = static_cast<b2Body*>(rb->getBody());
		body->CreateFixture(&fixtureDef);

		//DEBUG box
		if(auto comp = getOwner()->getComponent<DebugBoxComponent>())
		{
			m_pDebugBox = comp;
		}
		else
		{
			getOwner()->addComponent<DebugBoxComponent>(RiftColor::Cyan, m_info.size,m_info.debugVisualize);
		}

	}

}
