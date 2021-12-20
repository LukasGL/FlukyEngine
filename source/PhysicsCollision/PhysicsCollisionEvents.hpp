#pragma once
#ifndef PHYSICSCOLLISIONEVENTS_HPP
#define PHYSICSCOLLISIONEVENTS_HPP
#include <iostream>
#include "RigidBodyComponent.hpp"
#include "CollisionInformation.hpp"
namespace Fluky {

	struct StartCollisionEvent {
		/*StartCollisionEvent(RigidBodyComponent& rb0, RigidBodyComponent& rb1, bool swaped, CollisionInformation& info) :
			firstRigidBody(rb0),
			secondRigidBody(rb1),
			areSwaped(swaped),
			collisionInfo(info)
		{
		}*/
		RigidBodyComponent& firstRigidBody;
		RigidBodyComponent& secondRigidBody;
		bool areSwaped;
		CollisionInformation& collisionInfo;

	};

	struct EndCollisionEvent {
		/*EndCollisionEvent(RigidBodyComponent& rb0, RigidBodyComponent& rb1) :
			firstRigidBody(rb0),
			secondRigidBody(rb1)
		{}*/
		RigidBodyComponent& firstRigidBody;
		RigidBodyComponent& secondRigidBody;
	};

}
#endif