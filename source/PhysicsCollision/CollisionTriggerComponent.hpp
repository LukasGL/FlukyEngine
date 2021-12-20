#pragma once
#ifndef COLLISIONTRIGGERCOMPONENT_HPP
#define COLLISIONTRIGGERCOMPONENT_HPP
#include "../World/TransformComponent.hpp"
#include "PhysicsCollisionSystem.hpp"
#include <btBulletDynamicsCommon.h>
#include <set>
#include <tuple>

namespace Fluky {
	class World;
	class CollisionTriggerComponent {

	public:

		friend class PhysicsCollisionSystem;

		void CreateCollisionTriggerBody(PhysicsCollisionSystem* phySys, Fluky::Vec3 shape, Fluky::Vec3 origin) {

			btBoxShape* colShape = new btBoxShape(btVector3(shape.x, shape.y, shape.z));
			
			ghostBody = phySys->AddCollisionTriggerBody(colShape, btVector3(origin.x, origin.y, origin.z));

			int collisionFlags = ghostBody->getCollisionFlags();
			collisionFlags = btCollisionObject::CF_DYNAMIC_OBJECT;
			ghostBody->setCollisionFlags(collisionFlags);

			ghostBody->setActivationState(ACTIVE_TAG);
		}

		Fluky::Vec3 GetLocation() {
			btVector3 v = ghostBody->getWorldTransform().getOrigin();
			return Fluky::Vec3(v.getX(), v.getY(), v.getZ());
		}

		btTransform GetTransform() {
			return ghostBody->getWorldTransform();
		}

		void SetPosition(Fluky::Vec3 force) {

		}

	private:

		btGhostObject* ghostBody;

	};
}


#endif