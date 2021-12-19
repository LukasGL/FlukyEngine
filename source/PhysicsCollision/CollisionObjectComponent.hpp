#pragma once
#ifndef COLLISIONOBJECTCOMPONENT_HPP
#define COLLISIONOBJECTCOMPONENT_HPP
#include "../World/TransformComponent.hpp"
#include "PhysicsCollisionSystem.hpp"
#include <btBulletDynamicsCommon.h>
#include <set>
#include <tuple>

namespace Fluky {
	class World;
	class CollisionObjectComponent {
	
	public:

		friend class PhysicsCollisionSystem;

		void CreateRigidBody(PhysicsCollisionSystem* phySys, Fluky::Vec3 shape, float in_mass, Fluky::Vec3 origin) {

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
		}

		Fluky::Vec3 GetLocation() {
			btVector3 v = rigidBody->getWorldTransform().getOrigin();
			return Fluky::Vec3(v.getX(), v.getY(), v.getZ());
		}

		btTransform GetTransform() {
			return rigidBody->getWorldTransform();
		}

		void SetPosition(Fluky::Vec3 force) {
			//rigidBody->setActivationState(ACTIVE_TAG);
			//rigidBody->setLinearVelocity(btVector3(velocity.x, velocity.y, velocity.z));
			//rigidBody->getWorldTransform().setOrigin(btVector3(pos.x, pos.y, pos.z));
			//rigidBody->applyCentralForce(btVector3(pos.x, pos.y, pos.z));
			//rigidBody->applyCentralPushImpulse(btVector3(pos.x, pos.y, pos.z));
			rigidBody->setActivationState(ACTIVE_TAG);
			const btVector3& bulletForce = btVector3(force.x, force.y, force.z);
			const btVector3& bulletPos = btVector3(0.f, 0.f, 0.f);
			//rigidBody->clearForces();
			//rigidBody->applyForce(bulletForce, bulletPos);
			//rigidBody->applyCentralImpulse(bulletForce);
			//rigidBody->getLinearDamping()
			/*if (bulletForce.getX() == 0.f && bulletForce.getZ() == 0.f) {
				rigidBody->setLinearVelocity(btVector3(0.f, rigidBody->getLinearVelocity().getY(), 0.f));
				std::cout << "nofuerza" << std::endl;
			}
			else {
				rigidBody->setLinearVelocity(bulletForce + btVector3(0.f, rigidBody->getLinearVelocity().getY(), 0.f));
			}*/

			rigidBody->setLinearVelocity(bulletForce + btVector3(0.f, rigidBody->getLinearVelocity().getY(), 0.f));
			std::cout << rigidBody->getLinearVelocity().getX() << " " << rigidBody->getLinearVelocity().getY() << " " << rigidBody->getLinearVelocity().getZ() << std::endl;
			//std::cout << rigidBody->getTotalForce().getX() << " " << rigidBody->getTotalForce().getY() << " " << rigidBody->getTotalForce().getZ() << std::endl;
			//rigidBody->applyForce(bulletForce, bulletPos);
		}

	private:

		btRigidBody* rigidBody;

	};
}


#endif