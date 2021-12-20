#pragma once
#ifndef RIGIDBODYCOMPONENT_HPP
#define RIGIDBODYCOMPONENT_HPP
#include "../World/TransformComponent.hpp"
#include "PhysicsCollisionSystem.hpp"
#include <btBulletDynamicsCommon.h>
#include <set>
#include <tuple>

namespace Fluky {
	class World;
	class RigidBodyComponent {
	
	public:

		friend class PhysicsCollisionSystem;

		void CreateRigidBody(PhysicsCollisionSystem* phySys, Fluky::Vec3 shape, float in_mass, Fluky::Vec3 origin, bool IsTrigger = false) {

			btBoxShape* colShape = new btBoxShape(btVector3(shape.x, shape.y, shape.z));

			btTransform startTransform;
			startTransform.setIdentity();
			btScalar mass(in_mass);
			//rigidbody is dynamic if and only if mass is non zero, otherwise static
			bool isDynamic = (mass != 0.f);
			btVector3 localInertia(0, 0, 0);
			if (isDynamic) {
				colShape->calculateLocalInertia(mass, localInertia);
			}

			startTransform.setOrigin(btVector3(origin.x, origin.y, origin.z));

			

			rigidBody = phySys->AddRigidBody(mass, startTransform, colShape);


			if (IsTrigger) {
				int collisionFlags = rigidBody->getCollisionFlags();
				collisionFlags |= btCollisionObject::CF_NO_CONTACT_RESPONSE;
				rigidBody->setCollisionFlags(collisionFlags);
			}
		}

		void CreateCollisionTriggerBody(PhysicsCollisionSystem* phySys, Fluky::Vec3 shape, Fluky::Vec3 origin) {

			btBoxShape* colShape = new btBoxShape(btVector3(shape.x, shape.y, shape.z));



		}

		Fluky::Vec3 GetLocation() {
			btVector3 v = rigidBody->getWorldTransform().getOrigin();
			return Fluky::Vec3(v.getX(), v.getY(), v.getZ());
		}

		btTransform GetTransform() {
			return rigidBody->getWorldTransform();
		}

		void SetPosition(Fluky::Vec3 force) {

			rigidBody->setActivationState(ACTIVE_TAG);
			const btVector3& bulletForce = btVector3(force.x, force.y, force.z);
			const btVector3& bulletPos = btVector3(0.f, 0.f, 0.f);

			rigidBody->setLinearVelocity(bulletForce + btVector3(0.f, rigidBody->getLinearVelocity().getY(), 0.f));
		}

	private:

		btRigidBody* rigidBody;

	};
}


#endif