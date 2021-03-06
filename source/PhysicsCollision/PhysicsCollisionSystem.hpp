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

		void Update(float timeStep) { 
			m_worldPtr->stepSimulation(timeStep); 
		}

		btRigidBody* AddRigidBody(float mass, const btTransform& startTransform, btCollisionShape* shape, int gameObjectID, int group = 1, int mask = 1, const btVector4& color = btVector4(1, 0, 0, 1));

		btGhostObject* AddCollisionTriggerBody(btCollisionShape* shape, btVector3 origin);

		//void AddRigidBody(RigidBodyComponent& component) noexcept;
		//void RemoveRigidBody(RigidBodyComponent& component) noexcept;
		void ShutDown() noexcept;
		btDynamicsWorld* GetPhysicsWorldPtr() noexcept { return m_worldPtr; }

		void  SubmitCollisionEvents(World& world) noexcept;

		using CollisionPair = std::tuple<const btRigidBody*, const btRigidBody*, bool, int>;
		//struct cmp {
		//	//bool operator()(const CollisionPair& lhs, const CollisionPair& rhs) const {
		//	//	return (bool)(std::get<0>(lhs) < std::get<0>(rhs)) || (!(bool)(std::get<0>(rhs) < std::get<0>(lhs)) &&
		//	//		((bool)(std::get<1>(rhs) < std::get<1>(lhs))))
		//	//		;
		//	//	//return std::get<3>(lhs) < std::get<3>(rhs);
		//	//}
		//};
		using CollisionSet = std::set<CollisionPair>;

	private:
		btBroadphaseInterface* m_broadphasePtr;
		btCollisionConfiguration* m_collisionConfigurationPtr;
		btCollisionDispatcher* m_dispatcherPtr;
		btConstraintSolver* m_solverPtr;
		btDynamicsWorld* m_worldPtr;

		btAlignedObjectArray<btCollisionShape*> m_collisionShapes;
		//CollisionSet m_previousCollisionSet;
		CollisionSet m_previousCollisionSet;




	};
}


#endif