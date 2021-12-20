#include "PhysicsCollisionSystem.hpp"


#include "RigidBodyComponent.hpp"

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

		m_collisionShapes.push_back(shape);

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

	btCollisionObject* PhysicsCollisionSystem::AddCollisionTriggerBody(btCollisionShape* shape, btVector3 origin) {

		btGhostObject* body = new btGhostObject();

		body->setCollisionShape(shape);
		body->getWorldTransform().setOrigin(origin);

		m_worldPtr->addCollisionObject(body);
		return body;

	}

	void PhysicsCollisionSystem::SetPositionRigidBody(RigidBodyComponent obj, Fluky::Vec3 pos) {

		btRigidBody* rigidBody = obj.rigidBody;
		btVector3 localPivot = rigidBody->getWorldTransform().getOrigin();
		btPoint2PointConstraint* p2p = new btPoint2PointConstraint(*rigidBody, localPivot);
		m_worldPtr->addConstraint(p2p, true);
		btTypedConstraint* m_pickedConstraint = p2p;

		p2p->m_setting.m_impulseClamp = 30.f;
		//very weak constraint for picking
		p2p->m_setting.m_tau = 0.001f;

		btPoint2PointConstraint* pickCon = static_cast<btPoint2PointConstraint*>(m_pickedConstraint);
		if (pickCon)
		{
			//keep it at the same picking distance

			btVector3 newPivotB;

			btVector3 dir = rigidBody->getWorldTransform().getOrigin() - btVector3(pos.x, pos.y, pos.z);
			dir.normalize();
			//dir *= m_oldPickingDist;

			newPivotB = rigidBody->getWorldTransform().getOrigin() + dir;
			pickCon->setPivotB(newPivotB);
		}

	}

}