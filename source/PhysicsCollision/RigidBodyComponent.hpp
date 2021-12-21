#pragma once
#ifndef RIGIDBODYCOMPONENT_HPP
#define RIGIDBODYCOMPONENT_HPP
#include "../World/TransformComponent.hpp"
#include "PhysicsCollisionSystem.hpp"
#include <btBulletDynamicsCommon.h>
#include "CollisionInformation.hpp"
#include <set>
#include <tuple>
#include <functional>

namespace Fluky {
	class World;
	class RigidBodyComponent {
	
	public:

		friend class PhysicsCollisionSystem;

		using StartCollisionCallback = std::function<void(World&, RigidBodyComponent&, bool, CollisionInformation&)>;
		using EndCollisionCallback = std::function<void(World&, RigidBodyComponent&)>;

		void CreateRigidBody(World& w, Fluky::Vec3 shape, float in_mass, Fluky::Vec3 origin, int collisionGroup = 1, int collisionMask = 1);

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

		void SetStartCollisionCallback(StartCollisionCallback callback) {
			m_onStartCollisionCallback = callback;
		}
		void SetEndCollisionCallback(EndCollisionCallback callback) {
			m_onEndCollisionCallback = callback;
		}

		bool HasStartCollisionCallback() const {
			return (bool)m_onStartCollisionCallback;
		}

		bool HasEndCollisionCallback() const {
			return (bool)m_onEndCollisionCallback;
		}

		void CallStartCollisionCallback(World& world, RigidBodyComponent& rb, bool isSwaped, CollisionInformation& information) {
			m_onStartCollisionCallback(world, rb, isSwaped, information);
		}

		void CallEndCollisionCallback(World& world, RigidBodyComponent& rb) {
			m_onEndCollisionCallback(world, rb);
		}

		bool equal(RigidBodyComponent r) {
			return rigidBody == r.rigidBody;
		}

	private:

		btRigidBody* rigidBody;

		StartCollisionCallback m_onStartCollisionCallback;
		EndCollisionCallback m_onEndCollisionCallback;


	};
}


#endif