#pragma once
#ifndef BOXCOMPONENT_HPP
#define BOXCOMPONENT_HPP

#include "../World/Component.hpp"
#include "../World/TransformComponent.hpp"
#include "../PhysicsCollision/RigidBodyComponent.hpp"

namespace Fluky {
	/**
	 * Class that has to render the figures the user wants
	 */
	class BoxComponent : Component {

	public:
		friend class World;
		/**
		 * BoxComponent initializer
		   *
		 * @return {int}  :
		 */
		int Init();

  /**
   * BoxComponent destructor
   * 
   */
		~BoxComponent();
		/**
		 * Function called in every iteration of the main loop
		 */
		void Update() noexcept;

		unsigned int counter;

		bool initialized = false;

		float GetLocation(int i) {
			return transf->GetLocation(i);
		}

		float* GetMatrix() {
			return transf->GetMatrix();
		}

		void Translate(float x, float y, float z) {
			transf->Translate(x, y, z);
		}

		void SetPosition(float x, float y, float z) {
			transf->SetTranslation(x, y, z);
		}

		void RotateX(float angle) {
			transf->RotateX(angle);
		}
		void RotateY(float angle) {
			transf->RotateY(angle);
		}
		void RotateZ(float angle) {
			transf->RotateZ(angle);
		}
		void RotateXY(float angleX, float angleY) {
			transf->RotateXY(angleX, angleY);
		}
		void RotateXYZ(float angleX, float angleY, float angleZ) {
			transf->RotateXYZ(angleX, angleY, angleZ);
		}

		void AttachTo(RigidBodyComponent& c) {
			attached = true;
			*colobj = c;
		}

	private:

		TransformComponent* transf = new TransformComponent;

		bool attached = false;

		RigidBodyComponent* colobj = new RigidBodyComponent;
	};

}
#endif