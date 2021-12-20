#include "RigidBodyComponent.hpp"

#include "../World/World.hpp"


namespace Fluky {

	void RigidBodyComponent::CreateRigidBody(World& w, Fluky::Vec3 shape, float in_mass, Fluky::Vec3 origin, int collisionGroup, int collisionMask) {


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

		rigidBody = w.GetPhysicsSystem().AddRigidBody(mass, startTransform, colShape, w.GetGameObjects().size()-1, collisionGroup, collisionMask);

	}

}
