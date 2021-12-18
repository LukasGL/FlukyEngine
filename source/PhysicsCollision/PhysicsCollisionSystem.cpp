#include "PhysicsCollisionSystem.hpp"

namespace Fluky {

	void PhysicsCollisionSystem::InitPhysics() {

		CreateEmptyDynamicsWorld();

	}

	void PhysicsCollisionSystem::CreateEmptyDynamicsWorld() {

		m_collisionConfigurationPtr = new btDefaultCollisionConfiguration();

		m_dispatcherPtr = new btCollisionDispatcher(m_collisionConfigurationPtr);

		m_broadphasePtr = new btDbvtBroadphase();

		btSequentialImpulseConstraintSolver* sol = new btSequentialImpulseConstraintSolver;
		m_solverPtr = sol;

		m_worldPtr = new btDiscreteDynamicsWorld(m_dispatcherPtr, m_broadphasePtr, m_solverPtr, m_collisionConfigurationPtr);

		m_worldPtr->setGravity(btVector3(0, -10, 0));

	}

	btRigidBody* PhysicsCollisionSystem::AddRigidBody(float mass, const btTransform& startTransform, btCollisionShape* shape, const btVector4& color) {

		//rigidbody is dynamic if and only if mass is non zero, otherwise static
		bool isDynamic = (mass != 0.f);

		btVector3 localInertia(0, 0, 0);
		if (isDynamic)
			shape->calculateLocalInertia(mass, localInertia);

		//using motionstate is recommended, it provides interpolation capabilities, and only synchronizes 'active' objects

#define USE_MOTIONSTATE 1
#ifdef USE_MOTIONSTATE
		btDefaultMotionState* myMotionState = new btDefaultMotionState(startTransform);

		btRigidBody::btRigidBodyConstructionInfo cInfo(mass, myMotionState, shape, localInertia);

		btRigidBody* body = new btRigidBody(cInfo);
		//body->setContactProcessingThreshold(m_defaultContactProcessingThreshold);

#else
		btRigidBody* body = new btRigidBody(mass, 0, shape, localInertia);
		body->setWorldTransform(startTransform);
#endif  //

		body->setUserIndex(-1);
		m_worldPtr->addRigidBody(body);
		return body;
	}

}