#pragma once
#ifndef COLLISIONINFORMATION_HPP
#define COLLISIONINFORMATION_HPP
#include <vector>
#include "../World/TransformComponent.hpp"
#include <BulletCollision/NarrowPhaseCollision/btPersistentManifold.h>
namespace Fluky {
	struct ContactPoint {
	public:
		ContactPoint(const btVector3& positionOnA, const btVector3& positionOnB, const btVector3& normalOnB)
		{
			positionOnFirstBody = Fluky::Vec3(positionOnA.x(), positionOnA.y(), positionOnA.z());
			positionOnSecondBody = Fluky::Vec3(positionOnB.x(), positionOnB.y(), positionOnB.z());
			normalOnSecondBody = Fluky::Vec3(normalOnB.x(), normalOnB.y(), normalOnB.z());
		}
		Fluky::Vec3 positionOnFirstBody;
		Fluky::Vec3 positionOnSecondBody;
		Fluky::Vec3 normalOnSecondBody;
	};
	class CollisionInformation {
	public:
		using size_type = std::vector<ContactPoint>::size_type;
		CollisionInformation(const btPersistentManifold* manifold) {
			auto numContacts = manifold->getNumContacts();
			m_contactPoints.reserve(numContacts);
			for (int i = 0; i < numContacts; i++) {
				const btManifoldPoint& cp = manifold->getContactPoint(i);
				m_contactPoints.emplace_back(cp.getPositionWorldOnA(), cp.getPositionWorldOnB(), cp.m_normalWorldOnB);
			}
		}
		const ContactPoint& GetCollisionPoint(size_type index) const {
			return m_contactPoints[index];
		}
		size_type GetNumContactPoints() const {
			return m_contactPoints.size();
		}

	private:
		std::vector<ContactPoint> m_contactPoints;
	};
}
#endif