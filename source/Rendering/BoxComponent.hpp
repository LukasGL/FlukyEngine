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

		void SetShape(Fluky::Vec3 s) {
			shape = s;
			/*for (int i = 0; i < 8; i++) {
				this->s_cubeVertices[i].m_x *= shape.x;
				this->s_cubeVertices[i].m_y *= shape.y;
				this->s_cubeVertices[i].m_z *= shape.z;
			}*/
			transf->ScaleMtx(s);
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

		struct PosColorVertex
		{
			float m_x;
			float m_y;
			float m_z;
			uint32_t m_abgr;
		};

		

	private:

		PosColorVertex s_cubeVertices[8] = {
				{-1.0f,  1.0f,  1.0f, 0xff000000 },
				{ 1.0f,  1.0f,  1.0f, 0xff0000ff },
				{-1.0f, -1.0f,  1.0f, 0xff00ff00 },
				{ 1.0f, -1.0f,  1.0f, 0xff00ffff },
				{-1.0f,  1.0f, -1.0f, 0xffff0000 },
				{ 1.0f,  1.0f, -1.0f, 0xffff00ff },
				{-1.0f, -1.0f, -1.0f, 0xffffff00 },
				{ 1.0f, -1.0f, -1.0f, 0xffffffff },
		};

		Fluky::Vec3 shape = Fluky::Vec3(1.f, 1.f, 1.f);

		TransformComponent* transf = new TransformComponent;

		bool attached = false;

		RigidBodyComponent* colobj = new RigidBodyComponent;

	};

}
#endif