#pragma once
#ifndef COLLISIONOBJECTCOMPONENT_HPP
#define COLLISIONOBJECTCOMPONENT_HPP
#include "PhysicsCollisionSystem.hpp"
#include <btBulletDynamicsCommon.h>
#include <set>
#include <tuple>

namespace Fluky {
	class World;
	class CollisionObjectComponent {
	
	public:

		void CreateRigidBody(PhysicsCollisionSystem* phySys, Fluky::Vec3 shape, float in_mass, Fluky::Vec3 origin) {

			btBoxShape* colShape = new btBoxShape(btVector3(shape.x, shape.y, shape.z));

			btTransform startTransform;
			startTransform.setIdentity();
			btScalar mass(in_mass);
			//rigidbody is dynamic if and only if mass is non zero, otherwise static
			bool isDynamic = (mass != 0.f);
			btVector3 localInertia(0, 0, 0);
			if (isDynamic)
				colShape->calculateLocalInertia(mass, localInertia);

			startTransform.setOrigin(btVector3(origin.x, origin.y, origin.z));

			rigidBody = phySys->AddRigidBody(mass, startTransform, colShape);
		}

		Fluky::Vec3 GetLocation() {
			btVector3 v = rigidBody->getWorldTransform().getOrigin();
			return Fluky::Vec3(v.getX(), v.getY(), v.getZ());
		}

		btTransform GetTransform() {
			return rigidBody->getWorldTransform();
		}

	private:

		btRigidBody* rigidBody;

	};
}


#endif