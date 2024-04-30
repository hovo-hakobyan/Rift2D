#include "Physics.h"
#include <box2d/b2_world.h>
#include <glm/vec2.hpp>
#include <box2d/b2_body.h>
#include "TimeManager.h"
#include "Utils.h"

namespace rift2d
{
	class Physics::Impl
	{
	public:

		Impl()
		:m_physicsWorld(std::make_unique<b2World>(b2Vec2{0.f,0.f})),
		m_positionIterations{2},
		m_velocityIterations{6}
		{}

		void update()
		{
			m_physicsWorld->Step(TimeManager::GetInstance().getFixedTime(), m_velocityIterations, m_positionIterations);
		}

		void* createRigidBody(const RigidBodyDef& bodyDef) const
		{
			b2BodyDef b2bDef;
			b2bDef.type = RiftToBox2DBody(bodyDef.type);
			const glm::vec2 posMeters = Utils::pixelToMeters(glm::vec2{ bodyDef.pos.x,bodyDef.pos.y });
			b2bDef.position.Set(posMeters.x, posMeters.y);
			b2bDef.fixedRotation = bodyDef.fixedRotation;

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
	private:
		std::unique_ptr<b2World> m_physicsWorld;
		int32_t m_positionIterations;
		int32_t m_velocityIterations;
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

	
}

