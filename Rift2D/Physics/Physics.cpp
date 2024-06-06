#include "Physics.h"
#include <box2d/b2_world.h>
#include <glm/vec2.hpp>
#include <box2d/b2_body.h>

#include "ContactListener.h"
#include "World.h"
#include "Utils.h"
#include "PhysicsConfig.h"

namespace rift2d
{
	class Physics::Impl
	{
	public:

		Impl()
		:m_physicsWorld(std::make_unique<b2World>(b2Vec2{0.f,physics::DEFAULT_GRAVITY}))
		{
			m_physicsWorld->SetContactListener(new ContactListener());
		}

		void update()
		{
			if (m_isDisabled) return;
			m_physicsWorld->Step(World::GetInstance().getFixedTime(),static_cast<uint32>( physics::VELOCITY_ITERATIONS),static_cast<uint32>(physics::POSITION_ITERATIONS));
		}

		void* createRigidBody(const RigidBodyDef& bodyDef) const
		{
			b2BodyDef b2bDef;
			b2bDef.type = RiftToBox2DBody(bodyDef.type);
			const glm::vec2 posMeters = Utils::pixelToMeters(glm::vec2{ bodyDef.pos.x,bodyDef.pos.y });
			b2bDef.position.Set(posMeters.x, posMeters.y);
			b2bDef.fixedRotation = bodyDef.fixedRotation;
			b2bDef.userData = bodyDef.data;

			return m_physicsWorld->CreateBody(&b2bDef);
		}
		static b2BodyType RiftToBox2DBody(RiftBodyType type)
		{
			switch (type)
			{
			case RiftBodyType::Static: return b2_staticBody;
			case RiftBodyType::Dynamic: return b2_dynamicBody;
			case RiftBodyType::Kinematic:return b2_kinematicBody;
			}
			return b2_staticBody;
		}

		void destroyRigidBody(void* body)
		{
			auto physicsBody = static_cast<b2Body*>(body);
			if (physicsBody)
			{
				m_physicsWorld->DestroyBody(physicsBody);
			}
		}

		void enable()
		{
			m_isDisabled = false;
		}

		void disable()
		{
			m_isDisabled = true;
		}
	private:
		std::unique_ptr<b2World> m_physicsWorld;
		std::unique_ptr<ContactListener> m_contactListener;
		bool m_isDisabled{ false };
	};

	Physics::Physics() :
		m_pImpl(std::make_unique<Impl>())
	{}
	Physics::~Physics() = default;

	void Physics::update()
	{
		m_pImpl->update();
	}

	void* Physics::createRigidBody(const RigidBodyDef& bodyDef) const
	{
		return m_pImpl->createRigidBody(bodyDef);
	}

	void Physics::destroyRigidBody(void* body)
	{
		m_pImpl->destroyRigidBody(body);
	}

	void Physics::disable()
	{
		m_pImpl->disable();
	}

	void Physics::enable()
	{
		m_pImpl->enable();
	}
}

