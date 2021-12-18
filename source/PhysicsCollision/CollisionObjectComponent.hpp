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

		void CreateRigidBody(PhysicsCollisionSystem* phySys, btVector3 shape, float in_mass, btVector3 origin) {

			btBoxShape* colShape = new btBoxShape(shape);

			btTransform startTransform;
			startTransform.setIdentity();
			btScalar mass(in_mass);
			//rigidbody is dynamic if and only if mass is non zero, otherwise static
			bool isDynamic = (mass != 0.f);
			btVector3 localInertia(0, 0, 0);
			if (isDynamic)
				colShape->calculateLocalInertia(mass, localInertia);

			startTransform.setOrigin(origin);

			rigidBody = phySys->AddRigidBody(mass, startTransform, colShape);
		}

	private:

		btRigidBody* rigidBody;

	};
}


#endif