#pragma once
#ifndef PHYSICSCOLLISIONSYSTEM_HPP
#define PHYSICSCOLLISIONSYSTEM_HPP
#include "../World/TransformComponent.hpp"
#include <btBulletDynamicsCommon.h>
#include "btBulletCollisionCommon.h"
#include "BulletCollision/CollisionDispatch/btGhostObject.h"
#include <set>
#include <tuple>

namespace Fluky {
	class World;
	class PhysicsCollisionSystem {
	public:
		/*PhysicsCollisionSystem() {
			m_collisionConfigurationPtr = new btDefaultCollisionConfiguration();
			m_dispatcherPtr = new btCollisionDispatcher(m_collisionConfigurationPtr);
			m_broadphasePtr = new btDbvtBroadphase();
			m_solverPtr = new btSequentialImpulseConstraintSolver();
			m_worldPtr = new btDiscreteDynamicsWorld(m_dispatcherPtr, m_broadphasePtr, m_solverPtr, m_collisionConfigurationPtr);
		}*/
		~PhysicsCollisionSystem() {
			delete m_worldPtr;
			delete m_solverPtr;
			delete m_broadphasePtr;
			delete m_dispatcherPtr;
			delete m_collisionConfigurationPtr;

		}
		//void SetGravity(const glm::vec3& gravity) noexcept;
		//Fluky::Vec3 GetGravity() const noexcept;

		void CreateEmptyDynamicsWorld();

		void InitPhysics();

		void Update(float timeStep) { m_worldPtr->stepSimulation(timeStep); }

		void SetPositionRigidBody(class RigidBodyComponent obj, Fluky::Vec3 pos);

		btRigidBody* AddRigidBody(float mass, const btTransform& startTransform, btCollisionShape* shape, const btVector4& color = btVector4(1, 0, 0, 1));

		btCollisionObject* AddCollisionTriggerBody(btCollisionShape* shape, btVector3 origin);

		//void AddRigidBody(RigidBodyComponent& component) noexcept;
		//void RemoveRigidBody(RigidBodyComponent& component) noexcept;
		void ShutDown() noexcept;
		btDynamicsWorld* GetPhysicsWorldPtr() noexcept { return m_worldPtr; }


	private:
		btBroadphaseInterface* m_broadphasePtr;
		btCollisionConfiguration* m_collisionConfigurationPtr;
		btCollisionDispatcher* m_dispatcherPtr;
		btConstraintSolver* m_solverPtr;
		btDynamicsWorld* m_worldPtr;

		btAlignedObjectArray<btCollisionShape*> m_collisionShapes;
		//CollisionSet m_previousCollisionSet;




	};
}


#endif