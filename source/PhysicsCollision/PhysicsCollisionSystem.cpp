#include "PhysicsCollisionSystem.hpp"


#include "RigidBodyComponent.hpp"
#include "CollisionInformation.hpp"
#include "../World/GameObject.hpp"
#include "../World/World.hpp"
#include <algorithm>
#include <vector>
#include <iostream>

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

	btRigidBody* PhysicsCollisionSystem::AddRigidBody(float mass, const btTransform& startTransform, btCollisionShape* shape, int gameObjectID, int group, int mask, const btVector4& color) {

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

		body->setUserIndex(gameObjectID);
		m_worldPtr->addRigidBody(body, group , mask);
		return body;
	}

	btGhostObject* PhysicsCollisionSystem::AddCollisionTriggerBody(btCollisionShape* shape, btVector3 origin) {

		btGhostObject* body = new btGhostObject();

		body->setCollisionShape(shape);
		body->getWorldTransform().setOrigin(origin);

		m_worldPtr->addCollisionObject(body);
		return body;

	}

	void  PhysicsCollisionSystem::SubmitCollisionEvents(World& world) noexcept
	{
		CollisionSet currentCollisionSet;

		auto manifoldNum = m_dispatcherPtr->getNumManifolds();
		//Primero se pobla currentCollisionSet con las collisiones en esta iteración
		for (decltype(manifoldNum) i = 0; i < manifoldNum; i++) {
			btPersistentManifold* manifoldPtr = m_dispatcherPtr->getManifoldByIndexInternal(i);
			auto numContacts = manifoldPtr->getNumContacts();
			if (numContacts > 0) {
				const btRigidBody* body0 = static_cast<const btRigidBody*>(manifoldPtr->getBody0());
				const btRigidBody* body1 = static_cast<const btRigidBody*>(manifoldPtr->getBody1());
				const bool shouldSwap = body0 > body1;
				const btRigidBody* firstSortedBody = shouldSwap ? body1 : body0;
				const btRigidBody* secondSortedBody = shouldSwap ? body0 : body1;
				CollisionPair currentCollisionPair = std::make_tuple(firstSortedBody, secondSortedBody, shouldSwap, i);
				currentCollisionSet.insert(currentCollisionPair);
			}
		}
		int a = 0;
		CollisionSet newCollisions;

		//Para encontrar las colisiones nuevas es necesario encontrar las colisiones que estan presentes en la iteración actual
		//pero no en la anterior.
		std::set_difference(currentCollisionSet.begin(), currentCollisionSet.end(),
			m_previousCollisionSet.begin(), m_previousCollisionSet.end(),
			std::inserter(newCollisions, newCollisions.end()));


		std::vector<std::tuple<RigidBodyComponent, RigidBodyComponent, bool, CollisionInformation>> newCollisionsInformation;
		//A partir del conjunto de colisiones nuevas poblado con byRigidBody* se genera un conjunto 
		// con una representación interna RigidBodyHandle.
		newCollisionsInformation.reserve(newCollisions.size());
		for (auto& newCollision : newCollisions)
		{
			auto& rb0 = std::get<0>(newCollision);
			auto& rb1 = std::get<1>(newCollision);
			RigidBodyComponent go0 = world.GetGameObjects().at(rb0->getUserIndex()).GetComponent<RigidBodyComponent>();
			RigidBodyComponent go1 = world.GetGameObjects().at(rb1->getUserIndex()).GetComponent<RigidBodyComponent>();
			newCollisionsInformation.emplace_back(std::make_tuple(go0, go1, std::get<2>(newCollision), CollisionInformation(m_dispatcherPtr->getManifoldByIndexInternal(std::get<3>(newCollision)))));
			/*
			InnerComponentHandle rbhandle0 = InnerComponentHandle(rb0->getUserIndex(), rb0->getUserIndex2());
			InnerComponentHandle rbHandle1 = InnerComponentHandle(rb1->getUserIndex(), rb1->getUserIndex2());
			newCollisionsInformation.emplace_back(std::make_tuple(RigidBodyHandle(rbhandle0, &rigidBodyDatamanager),
				RigidBodyHandle(rbHandle1, &rigidBodyDatamanager),
				std::get<2>(newCollision),
				CollisionInformation(m_dispatcherPtr->getManifoldByIndexInternal(std::get<3>(newCollision)))));*/
		}

		//Se procede a llamar las callbacks correspondientes de cada RigidBodyComponent entrando en una nueva colision.
		//Este proceso podría hacerse en el paso anterior, pero dado que callbacks podrían eliminar componentes en uso en ese momento
		//es necesario posponer este proceso.
		for (auto& collisionInformation : newCollisionsInformation) {
			auto& rb0 = std::get<0>(collisionInformation);
			auto& rb1 = std::get<1>(collisionInformation);
			auto& collisionInfo = std::get<3>(collisionInformation);
			if (rb0.HasStartCollisionCallback()) {
				rb0.CallStartCollisionCallback(world, rb1, std::get<2>(collisionInformation), collisionInfo);
			}
			if (rb1.HasStartCollisionCallback()) {
				rb1.CallStartCollisionCallback(world, rb1, !std::get<2>(collisionInformation), collisionInfo);
			}
			//Ademas se publica el evento de colision a travez del eventManager
		}

		//El mismo proceso es necesario para colisiones que estan terminando.
		CollisionSet removedCollisions;
		std::set_difference(m_previousCollisionSet.begin(), m_previousCollisionSet.end(),
			currentCollisionSet.begin(), currentCollisionSet.end(),
			std::inserter(removedCollisions, removedCollisions.begin()));
		std::vector <std::tuple<RigidBodyComponent, RigidBodyComponent>> removedCollisionInformation;

		for (auto& removedCollision : removedCollisions)
		{
			auto& rb0 = std::get<0>(removedCollision);
			auto& rb1 = std::get<1>(removedCollision);
			RigidBodyComponent go0 = world.GetGameObjects().at(rb0->getUserIndex()).GetComponent<RigidBodyComponent>();
			RigidBodyComponent go1 = world.GetGameObjects().at(rb1->getUserIndex()).GetComponent<RigidBodyComponent>();
			removedCollisionInformation.emplace_back(std::make_tuple(go0, go1));
			/*InnerComponentHandle rbhandle0 = InnerComponentHandle(rb0->getUserIndex(), rb0->getUserIndex2());
			InnerComponentHandle rbHandle1 = InnerComponentHandle(rb1->getUserIndex(), rb1->getUserIndex2());
			removedCollisionInformation.emplace_back(std::make_tuple(RigidBodyHandle(rbhandle0, &rigidBodyDatamanager),
				RigidBodyHandle(rbHandle1, &rigidBodyDatamanager)));*/
		}

		for (auto& collisionInformation : removedCollisionInformation) {
			auto& rb0 = std::get<0>(collisionInformation);
			auto& rb1 = std::get<1>(collisionInformation);
			if (rb0.HasEndCollisionCallback()) {
				rb0.CallEndCollisionCallback(world, rb1);
			}
			if (rb1.HasEndCollisionCallback()) {
				rb1.CallEndCollisionCallback(world, rb0);
			}
		}
		m_previousCollisionSet = currentCollisionSet;

	}



	

}