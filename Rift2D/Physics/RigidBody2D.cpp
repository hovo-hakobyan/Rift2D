#include "RigidBody2D.h"

#include <iostream>

#include "GameObject.h"
#include "Physics.h"
#include "Transform.h"
#include "Utils.h"
#include <box2d/b2_body.h>

namespace rift2d
{
	class RigidBody2D::Impl
	{
	public:
		Impl(GameObject* owner, const RigidBodyDef& bodyDef):
		m_bodyDef(bodyDef),
		m_pOwner(owner){}

		void init()
		{
			const auto transform = m_pOwner->getTransform();
			const auto pos = transform->getWorldPosition();
			m_bodyDef.pos = glm::vec2{ pos.x,pos.y };

			m_pBody = static_cast<b2Body*>(Physics::GetInstance().createRigidBody(m_bodyDef));
			m_pBody->SetLinearDamping(m_bodyDef.linearDamping);
		}

		void update()
		{
			const auto newPos = m_pBody->GetPosition();
			const auto transform = m_pOwner->getTransform();
			transform->setWorldPosition(Utils::metersToPixels(glm::vec2{ newPos.x,newPos.y }));

		
		}

		void setLinearVelocity(const glm::vec2 v) const
		{
			m_pBody->SetLinearVelocity({ v.x,v.y });
		}

		void applyLinearImpulse(const glm::vec2 impulse, const glm::vec2 point) const
		{
			m_pBody->ApplyLinearImpulse({ impulse.x,impulse.y }, { point.x,point.y },true);
		}

		void setLinearDamping(float damping) const
		{
			m_pBody->SetLinearDamping(damping);
		}

		void setRotation(glm::vec2 dir) const
		{
			float rot = std::atan2(dir.y, dir.x);
			m_pOwner->getTransform()->setLocalRotation(rot);
		}

		void* getBody() const
		{
			return m_pBody;
		}
	private:
		RigidBodyDef m_bodyDef{};
		b2Body* m_pBody{};
		GameObject* m_pOwner{};
	};


	RigidBody2D::RigidBody2D(GameObject* owner, RigidBodyDef bodyDef) :
		BaseComponent(owner),
		m_pImpl(std::make_unique<Impl>(owner,bodyDef))
	{}

	RigidBody2D::~RigidBody2D() = default;

	void RigidBody2D::init()
	{
		BaseComponent::init();

		m_pImpl->init();
	}

	void RigidBody2D::update()
	{
		m_pImpl->update();
	}

	void RigidBody2D::setLinearVelocity(const glm::vec2 v) const
	{
		m_pImpl->setLinearVelocity(v);
	}

	void RigidBody2D::setLinearDamping(float damping) const
	{
		m_pImpl->setLinearDamping(damping);
	}

	void RigidBody2D::applyLinearImpulse(const glm::vec2 impulse, const glm::vec2 point) const
	{
		m_pImpl->applyLinearImpulse(impulse, point);
	}

	void RigidBody2D::setRotation(const glm::vec2 dir) const
	{
		m_pImpl->setRotation(dir);
	}

	void* RigidBody2D::getBody() const
	{
		return m_pImpl->getBody();
	}

}
