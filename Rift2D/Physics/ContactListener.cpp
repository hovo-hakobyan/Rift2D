#include "ContactListener.h"

#include <iostream>
#include <box2d/b2_contact.h>
#include "RigidBody2D.h"

namespace rift2d
{
	void ContactListener::BeginContact(b2Contact* contact)
	{

		auto* bodyA = static_cast<RigidBody2D*>(contact->GetFixtureA()->GetBody()->GetUserData());
		if (!bodyA) return;
		auto goA = bodyA->getOwner();

		auto* bodyB = static_cast<RigidBody2D*>(contact->GetFixtureB()->GetBody()->GetUserData());
		if (!bodyB) return;
		auto goB = bodyB->getOwner();

		bodyA->evaluateBeginOverlap(bodyA,bodyB,goA,goB);
		bodyB->evaluateBeginOverlap(bodyB,bodyA,goB,goA);
	}

	void ContactListener::EndContact(b2Contact* contact)
	{
		auto* bodyA = static_cast<RigidBody2D*>(contact->GetFixtureA()->GetBody()->GetUserData());
		if (!bodyA) return;
		auto goA = bodyA->getOwner();
		auto* bodyB = static_cast<RigidBody2D*>(contact->GetFixtureB()->GetBody()->GetUserData());
		if (!bodyB) return;
		auto goB = bodyB->getOwner();

		bodyA->evaluateEndOverlap(bodyA, bodyB, goA, goB);
		bodyB->evaluateEndOverlap(bodyB, bodyA, goB, goA);
	}
}
